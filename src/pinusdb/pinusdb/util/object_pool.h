#pragma once

#include <stdint.h>
#include "util/ker_list.h"

class ObjectPool
{
public:
  ObjectPool(int objSize, int maxCnt, int cntPerBlk);

  virtual ~ObjectPool();

  uint8_t* MallocObject();

  void FreeObject(uint8_t* pObj);

private:
  struct list_head freeList_;     // ��������

  int objSize_;                   // �����С
  int cntPerBlk_;                 // ÿ����洢�Ķ�����

  int maxBlkCnt_;                 // ��������
  int curBlkCnt_;                 // ��ǰ������
  uint8_t** ppBlk_;                  // ���ݿ�ָ��
};

