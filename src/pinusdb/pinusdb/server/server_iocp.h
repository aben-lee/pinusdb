/*
* Copyright (c) 2019 ChangSha JuSong Soft Inc. <service@pinusdb.cn>.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; version 3 of the License.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with this program; If not, see <http://www.gnu.org/licenses>
*/

#pragma once
#include "internal.h"

#include "util/object_pool.h"

#define SOCKET_CONTEXT_BUF_SIZE   (8 * 1024)

class IOCPEvent;

typedef enum _OPERATION_TYPE
{
  ACCEPT_POSTED = 0,      // Ͷ��Accept����
  RECV_POSTED = 1,        // Ͷ�ݽ��ղ���
  SEND_POSTED = 2,        // Ͷ�ݷ��Ͳ���
  NULL_POSTED = 3,        // ���ڳ�ʼ��
}OPERATION_TYPE;

class IOCPEvent;

typedef struct _SOCKET_CONTEXT
{
  SOCKET         socket_;         //�׽���
  OVERLAPPED     overlapped_;     //�ص���������
  OPERATION_TYPE opType_;         //��������
  WSABUF         wsaBuf_;         //�������
  IOCPEvent*     pEventHandle_;   //�¼�����
  char           dataBuf_[SOCKET_CONTEXT_BUF_SIZE]; //���ջ�����
}SOCKET_CONTEXT;

class ServerIOCP
{
public:
  ServerIOCP();
  virtual ~ServerIOCP();

public:
  bool LoadSocketLib();
  void UnloadSocketLib();

  virtual bool Start() = 0;
  virtual void Stop() = 0;

protected:
  bool InitIOCP();
  bool InitListenSocket();
  SOCKET_CONTEXT* DoAccept(SOCKET_CONTEXT* pContext, size_t bytesTransfered);

  virtual IOCPEvent* NewEvent(const char* pRemoteIp, int remotePort) = 0;
  virtual void RemoveEvent(IOCPEvent* pEvent) = 0;

  SOCKET_CONTEXT* DoFirstRecvWithData(SOCKET_CONTEXT* pContext, size_t bytesTransfered);

  SOCKET_CONTEXT* DoFirstRecvWithoutData(SOCKET_CONTEXT* pContext);

  bool PostAccept(SOCKET_CONTEXT* pContext);

  bool PostRecv(SOCKET_CONTEXT* pContext);
  bool PostSend(SOCKET_CONTEXT* pContext);

  bool StartIocp(const char* pSerIp, int serPort);
  void StopIocp();

  int GetProcessorsCnt();

  SOCKET_CONTEXT* MallocSocketContext();
  void FreeSocketContext(SOCKET_CONTEXT* pContext);

  static DWORD WINAPI WorkerThread(LPVOID lpParam);
  static DWORD WorkerMain(LPVOID lpParam);

  enum {
    kMaxWorkThreadCnt = 128,    //�����߳���
    kThreadsPerProcessor = 8,   //ÿһ�������������ж��ٸ��߳�
    kConcurrentPerProcessor = 4, //ÿһ����������ͬʱ������߳���

    kSocketListenCnt = 1,      //�����׽��ָ���
    kSocketAcceptCnt = 15,     //�ύ��Accept����
    kSocketWorkerCnt = 1024,   //�׽������Ӹ���

    kContextCntPerBlk = 16,     //һ���ڴ����64������
  };

protected:
  bool running_;
  HANDLE iocpHandle_;

  std::string serIP_;
  int         serPort_;

  SOCKET_CONTEXT* pListenContext_;

  LPFN_ACCEPTEX              lpfnAcceptEx_;
  LPFN_GETACCEPTEXSOCKADDRS  lpfnGetAcceptExSockAddrs_;

  int workThreadCnt_;
  HANDLE workThreads_[kMaxWorkThreadCnt];

  /////////////////////////////////////////////////////////////////

  std::mutex iocpMutex_;
  ObjectPool* pContextPool_;
};



