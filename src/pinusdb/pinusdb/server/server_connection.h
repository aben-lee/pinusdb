#pragma once

#include "internal.h"
#include "util/ker_list.h"
#include "query/result_filter.h"

typedef struct _ConnInfo
{
  int role_;
  int remotePort_;
  int64_t connTime_;
  char remoteHost_[IP_ADDR_STR_LEN];
  char loginName_[PDB_USER_NAME_LEN];
}ConnInfo;

class QueryParam;
class DataTable;

class ServerConnection
{
public:
  ServerConnection();
  ~ServerConnection();

  bool AddConnection(uint64_t connKey, const char* pRemoteHost, int remotePort);
  void ConnectionLogin(uint64_t connKey, const char* pLoginName, int role);

  void DelConnection(uint64_t connKey);

  PdbErr_t QueryConn(IResultFilter* pFilter);

private:
  enum {
    kConnCntPerBlk = 64,  //һ���ڴ����ConnInfo����ĸ���, ���� 8K
    kMaxBlkCnt = 16,     //�ڴ�����������Ҳ��������ܴ洢 256 * 16 = 4096 �����Ӷ���
  };

  ConnInfo* MallocConnInfo();

private:
  std::mutex connMutex_;
  std::unordered_map<uint64_t, ConnInfo*> connMap_;

  struct list_head freeConnList_;

  int blkCnt_;                //�ڴ������
  void* ppBlk_[kMaxBlkCnt];   //�ڴ������

};


