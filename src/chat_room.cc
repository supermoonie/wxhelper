#include "pch.h"
#include "chat_room.h"

#include "common.h"
#include "get_db_handle.h"
#include "wechat_data.h"
#include "base64.h"
using namespace std;

#define WX_CHAT_ROOM_MGR_OFFSET 0x67ee70
#define WX_GET_CHAT_ROOM_DETAIL_INFO_OFFSET 0xa73a80
#define WX_NEW_CHAT_ROOM_INFO_OFFSET 0xd07010
#define WX_FREE_CHAT_ROOM_INFO_OFFSET 0xd072f0
#define WX_DEL_CHAT_ROOM_MEMBER_OFFSET 0xa69a50
#define WX_INIT_CHAT_MSG_OFFSET 0xdbf380
#define WX_FREE_CHAT_MSG_OFFSET 0x649ac0
#define WX_ADD_MEMBER_TO_CHAT_ROOM_OFFSET 0xa69560
#define WX_GET_MEMBER_FROM_CHAT_ROOM_OFFSET 0xa749b0
#define WX_INIT_CHAT_ROOM_OFFSET 0xd04d80
#define WX_FREE_CHAT_ROOM_OFFSET 0xa7c620
#define WX_MOD_CHAT_ROOM_MEMBER_NICK_NAME_OFFSET 0xa6f8f0
#define WX_NEW_CHAT_MSG_OFFSET 0x64adc0
#define WX_TOP_MSG_OFFSET 0xa76e60
#define WX_REMOVE_TOP_MSG_OFFSET 0xa76c50

int GetChatRoomDetailInfo(wchar_t* chat_room_id, ChatRoomInfoInner& room_info) {
  int success = 0;
  WeChatString chat_room(chat_room_id);
  DWORD base = GetWeChatWinBase();
  DWORD get_chat_room_mgr_addr = base + WX_CHAT_ROOM_MGR_OFFSET;
  DWORD get_chat_room_detail_addr = base + WX_GET_CHAT_ROOM_DETAIL_INFO_OFFSET;
  DWORD create_chat_room_info_addr = base + WX_NEW_CHAT_ROOM_INFO_OFFSET;
  DWORD free_chat_room_info_addr = base + WX_FREE_CHAT_ROOM_INFO_OFFSET;
  char chat_room_info[0xDC] = {0};
  __asm {
         PUSHAD
         LEA        ECX,chat_room_info
         CALL       create_chat_room_info_addr
         CALL       get_chat_room_mgr_addr                                  
         PUSH       0x0
         LEA        ECX,chat_room_info
         PUSH       ECX
         LEA        ECX,chat_room
         PUSH       ECX
         MOV        ECX,EAX
         CALL       get_chat_room_detail_addr
         MOV        success,EAX  
         POPAD
  }
  DWORD room_id_len = *(DWORD*)(chat_room_info + 0x8);
  DWORD room_id_max_len = *(DWORD*)(chat_room_info + 0xC);
  wchar_t * room_id = new wchar_t[room_id_len + 1];
  wmemcpy(room_id,*(wchar_t**)(chat_room_info + 0x4),room_id_len + 1);
  room_info.chat_room_id.ptr = room_id;
  room_info.chat_room_id.length = room_id_len;
  room_info.chat_room_id.max_length = room_id_max_len;
  

  DWORD notice_len = *(DWORD*)(chat_room_info + 0x1C);
  DWORD notice_max_len = *(DWORD*)(chat_room_info + 0x20);
  wchar_t* notice_ptr = *(wchar_t**)(chat_room_info + 0x18);
  if(notice_len <= 0){
    room_info.notice.ptr = nullptr;
  }else{
    wchar_t * notice = new wchar_t[notice_len + 1];
    wmemcpy(notice,notice_ptr,notice_len+1);
    room_info.notice.ptr = notice;
  }
  room_info.notice.length = notice_len;
  room_info.notice.max_length = notice_max_len;

  DWORD admin_len = *(DWORD*)(chat_room_info + 0x30);
  DWORD admin_max_len = *(DWORD*)(chat_room_info + 0x34);
  wchar_t* admin_ptr = *(wchar_t**)(chat_room_info + 0x2C);
  if(admin_len <= 0){
    room_info.admin.ptr = nullptr;
  }else{
    wchar_t * admin = new wchar_t[admin_len + 1];
    wmemcpy(admin,admin_ptr,admin_len+1);
    room_info.admin.ptr = admin;
  }
  room_info.admin.length = admin_len;
  room_info.admin.max_length = admin_max_len;

  DWORD xml_len = *(DWORD*)(chat_room_info + 0x54);
  DWORD xml_max_len = *(DWORD*)(chat_room_info + 0x58);
  wchar_t* xml_ptr = *(wchar_t**)(chat_room_info + 0x50);
  if (xml_len <= 0){
    room_info.xml.ptr = nullptr;
  }else{
    wchar_t * xml = new wchar_t[xml_len + 1];
    wmemcpy(xml,xml_ptr,xml_len+1);
    room_info.xml.ptr = xml;
  }
  room_info.xml.length = xml_len;
  room_info.xml.max_length = xml_max_len;

  __asm {
        PUSHAD
        LEA         ECX,chat_room_info
        CALL        free_chat_room_info_addr
        POPAD
  }
  return success;
}

int DelMemberFromChatRoom(wchar_t* chat_room_id, wchar_t** wxids,int len) {
  int success = 0;
  WeChatString chat_room(chat_room_id);
  vector<WeChatString> members;
  VectorInner *list = (VectorInner *)&members;
  DWORD members_ptr = (DWORD)&list->start;
  for (int i = 0; i < len; i++) {
    WeChatString pwxid(wxids[i]);
    members.push_back(pwxid);
  }
  DWORD base = GetWeChatWinBase();
  DWORD get_chat_room_mgr_addr = base + WX_CHAT_ROOM_MGR_OFFSET;
  DWORD del_member_addr = base + WX_DEL_CHAT_ROOM_MEMBER_OFFSET;
  DWORD init_chat_msg_addr = base + WX_INIT_CHAT_MSG_OFFSET;
  __asm {
         PUSHAD
         CALL       get_chat_room_mgr_addr                              
         SUB        ESP,0x14
         MOV        ESI,EAX
         MOV        ECX,ESP
         LEA        EDI,chat_room
         PUSH       EDI
         CALL       init_chat_msg_addr    
         MOV        ECX,ESI
         MOV        EAX,dword ptr[members_ptr]
         PUSH       EAX
         CALL       del_member_addr   
         MOV        success,EAX        
         POPAD
  }
  return success;
}


int AddMemberToChatRoom(wchar_t* chat_room_id, wchar_t** wxids,int len){
 int success = 0;
  WeChatString chat_room(chat_room_id);
  vector<WeChatString> members;
  VectorInner *list = (VectorInner *)&members;
  DWORD members_ptr = (DWORD)&list->start;
  for (int i = 0; i < len; i++) {
    WeChatString pwxid(wxids[i]);
    members.push_back(pwxid);
  }
  DWORD base = GetWeChatWinBase();
  DWORD get_chat_room_mgr_addr = base + WX_CHAT_ROOM_MGR_OFFSET;
  DWORD add_member_addr = base + WX_ADD_MEMBER_TO_CHAT_ROOM_OFFSET;
  DWORD init_chat_msg_addr = base + WX_INIT_CHAT_MSG_OFFSET;
  DWORD temp=0;
  __asm {
         PUSHAD
         PUSHFD
         CALL       get_chat_room_mgr_addr 
         SUB        ESP,0x8
         MOV        temp,EAX
         MOV        ECX,ESP
         MOV        dword ptr [ECX],0x0
         MOV        dword ptr [ECX + 4],0x0
         TEST       ESI,ESI
         SUB        ESP,0x14
         MOV        ECX,ESP
         LEA        EAX,chat_room
         PUSH       EAX
         CALL       init_chat_msg_addr                                    
         MOV        ECX,temp
         MOV        EAX,dword ptr[members_ptr]
         PUSH       EAX
         CALL       add_member_addr
         MOV        success,EAX        
         POPFD
         POPAD
  }
  return success;
}


int GetMemberFromChatRoom(wchar_t* chat_room_id,ChatRoomInner & out){
  int success = 0;
   WeChatString chat_room(chat_room_id);
   DWORD chat_room_ptr = (DWORD) &chat_room;
  char buffer[0x1D4] = {0};
  DWORD base = GetWeChatWinBase();
  DWORD get_member_addr =  base + WX_GET_MEMBER_FROM_CHAT_ROOM_OFFSET;
  DWORD get_chat_room_mgr_addr = base + WX_CHAT_ROOM_MGR_OFFSET;
  DWORD create_chat_room_addr = base + WX_INIT_CHAT_ROOM_OFFSET;
  DWORD free_chat_room_addr = base + WX_FREE_CHAT_ROOM_OFFSET;
  __asm {
    PUSHAD
    LEA       ECX,buffer
    CALL      create_chat_room_addr
    CALL      get_chat_room_mgr_addr
    LEA       EAX, buffer
    PUSH      EAX
    PUSH      chat_room_ptr
    CALL      get_member_addr
    MOVZX     EAX,AL
    MOV       success,EAX
    POPAD
  }
  char* members  = *(char **)(buffer +0x1c);
  wchar_t* room  = *(wchar_t **)(buffer +0x8);
  wchar_t* admin  = *(wchar_t **)(buffer +0x4c);
 
  out.members = new char[strlen(members) + 1];
  memcpy(out.members, members, strlen(members) + 1);

  out.chat_room = new wchar_t[wcslen(room)+1];
  wmemcpy(out.chat_room ,room,wcslen(room)+1);

  out.admin = new wchar_t[wcslen(admin)+1];
  wmemcpy(out.admin ,admin,wcslen(admin)+1);

  __asm{
    LEA       ECX,buffer
    CALL      free_chat_room_addr
  }  
  return success;
}

int ModChatRoomMemberNickName(wchar_t* chat_room_id,wchar_t* wxid,wchar_t * nick){
  int success = 0;
  WeChatString chat_room(chat_room_id);
  WeChatString self_wxid(wxid);
  WeChatString new_nick(nick);
  DWORD base = GetWeChatWinBase();
  DWORD get_chat_room_mgr_addr = base + WX_CHAT_ROOM_MGR_OFFSET;
  DWORD mod_member_nick_name_addr = base + WX_MOD_CHAT_ROOM_MEMBER_NICK_NAME_OFFSET;
  DWORD init_chat_msg_addr = base + WX_INIT_CHAT_MSG_OFFSET;
  __asm{
    PUSHAD
    CALL       get_chat_room_mgr_addr                               
    SUB        ESP,0x14
    MOV        ECX,ESP
    LEA        EDI,new_nick
    PUSH       EDI
    CALL       init_chat_msg_addr                                      
    SUB        ESP,0x14
    LEA        EAX,self_wxid
    MOV        ECX,ESP
    PUSH       EAX
    CALL       init_chat_msg_addr                                      
    SUB        ESP,0x14
    LEA        EAX,chat_room
    MOV        ECX,ESP
    PUSH       EAX
    CALL       init_chat_msg_addr                                      
    CALL       mod_member_nick_name_addr   
    MOVZX     EAX,AL
    MOV       success,EAX      
    POPAD
  }
  return success;
}


int SetTopMsg(wchar_t* wxid,ULONG64 msg_id){
  int success = -1;
  char chat_msg[0x2A8] ={0};
  DWORD base = GetWeChatWinBase();
  DWORD new_chat_msg_addr = base + WX_NEW_CHAT_MSG_OFFSET;
  DWORD get_chat_room_mgr_addr = base + WX_CHAT_ROOM_MGR_OFFSET;
  DWORD handle_top_msg_addr = base + WX_TOP_MSG_OFFSET;
  DWORD free_addr = base +  WX_FREE_CHAT_ROOM_OFFSET;
  vector<string> local_msg = GetChatMsgByMsgId(msg_id);
  if(local_msg.empty()){
    return -2;
  }
  string  type = local_msg[3];
  string  status = local_msg[10];
  string  talker = local_msg[13];
  string  content = local_msg[14];
  wstring w_talker = String2Wstring(talker);
  wstring w_content = String2Wstring(content);
  int msg_type =stoi(type);
  int msg_status =stoi(status);

  #ifdef _DEBUG
  wcout << "w_talker:"  <<w_talker  <<endl;
  wcout << "w_content:"  <<w_content  <<endl;
  #endif
  WeChatString  chat_room(w_talker);
  WeChatString msg_content(w_content);

  WeChatString user_id(wxid);
  __asm{
    PUSHAD
    LEA        ECX,chat_msg
    CALL       new_chat_msg_addr
    POPAD
  }

  memcpy(&chat_msg[0x30],&msg_id,sizeof(msg_id));
  memcpy(&chat_msg[0x38],&msg_type,sizeof(msg_type));
  memcpy(&chat_msg[0x40],&msg_status,sizeof(msg_status));
  memcpy(&chat_msg[0x48],&chat_room,sizeof(chat_room));
 
  memcpy(&chat_msg[0x70],&msg_content,sizeof(msg_content));
  memcpy(&chat_msg[0x174],&user_id,sizeof(user_id));
 

  __asm{
    PUSHAD
    CALL       get_chat_room_mgr_addr                             
    PUSH       0x1
    LEA        EAX,chat_msg
    PUSH       EAX
    CALL       handle_top_msg_addr
    MOV        success,EAX
    LEA        ECX,chat_msg
    CALL       free_addr
    POPAD
  }
  return success;
}


int RemoveTopMsg(wchar_t* chat_room_id,ULONG64 msg_id){

  int success = -1;
  WeChatString chat_room(chat_room_id);
  DWORD base = GetWeChatWinBase();
  DWORD get_chat_room_mgr_addr = base + WX_CHAT_ROOM_MGR_OFFSET;
  DWORD new_chat_msg_addr = base + WX_NEW_CHAT_MSG_OFFSET;
  DWORD init_chat_msg_addr = base + WX_INIT_CHAT_MSG_OFFSET;
  DWORD remove_top_msg_addr = base + WX_REMOVE_TOP_MSG_OFFSET;

  __asm{
    PUSHAD
    CALL       get_chat_room_mgr_addr                                   
    MOV        EDI,dword ptr [msg_id]
    LEA        EAX,chat_room
    MOV        ESI,dword ptr [msg_id + 0x4]
    SUB        ESP,0x14
    MOV        ECX,ESP
    PUSH       EAX
    CALL       init_chat_msg_addr                                      
    PUSH       ESI
    PUSH       EDI
    CALL       remove_top_msg_addr     
    MOV        success,EAX 
    POPAD                               
  }

  return success;
}