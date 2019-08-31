#pragma once

#include "internal.h"
#include "util/object_pool.h"

class IOCPEvent
{
public:
  IOCPEvent()
  {
    eventState_ = EventState::kRecv;
  }
  virtual ~IOCPEvent()
  {
  }

  virtual bool RecvPostedEvent(const uint8_t* pBuf, size_t bytesTransfered) = 0;

  virtual bool SendPostedEvent(size_t bytesTransfered) = 0;

  virtual bool ExecTask() = 0;

  virtual bool GetRecvBuf(WSABUF* pWsaBuf) = 0;
  virtual bool GetSendBuf(WSABUF* pWsaBuf) = 0;

  enum EventState
  {
    kRecv = 1,     //���ڽ��ձ���
    kExec = 2,     //����ִ�л�ȴ���ִ��
    kSend = 3,  //���ڷ��ͷ��ر���
    kEnd = 4,   //ȫ���������ύ
  };

  inline int GetState() { return (eventState_); }

  inline bool IsEnd()
  {
    return eventState_ == EventState::kEnd;
  }

  inline void SetEnd()
  {
    eventState_ = EventState::kEnd;
  }

protected:
  int eventState_;                      //״̬

};