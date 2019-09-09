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