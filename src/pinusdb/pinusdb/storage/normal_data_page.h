#pragma once
#include "internal.h"
#include "storage/page_hdr.h"
#include "table/db_value.h"

typedef struct _NormalDataHead
{
  uint32_t pageCrc_;      //ҳ��У����
  int32_t  pageNo_;       //ҳ��
  int64_t  devId_;        //�豸ID
  int64_t  idxTs_;        //����ʱ���
  uint16_t recCnt_;       //��ǰ�洢�ļ�¼����
  uint16_t chipBytes_;    //�����ֽ���
  uint16_t freeBytes_;    //�����ֽ���
  uint16_t padding_;      //
}NormalDataHead;

#define UPDATE_NORMAL_DATA_PAGE_CRC(pDataHead) do \
{ \
  pDataHead->pageCrc_ = StringTool::CRC32(pDataHead, (NORMAL_PAGE_SIZE - sizeof(uint32_t)), sizeof(uint32_t)); \
}while(false)

class NormalDataPage
{
public:
  NormalDataPage();
  ~NormalDataPage();

  PdbErr_t Load(PageHdr* pPage);
  void Init(PageHdr* pPage, int32_t pageNo, int64_t devId, int64_t idxTs);

  int32_t GetPageNo() const;
  int64_t GetDevId() const;
  uint16_t GetRecCnt() const;
  uint16_t GetChipBytes() const;
  uint16_t GetFreeBytes() const;
  int64_t GetIdxTs() const;

  void UpdateCrc();

  PdbErr_t InsertRec(int64_t ts, const PdbByte* pRec, size_t recLen, bool replace);
  PdbErr_t GetRecData(size_t idx, const PdbByte** ppRec);
  PdbErr_t GetRecTstamp(size_t idx, int64_t* pTstamp);
  PdbErr_t GetLastTstamp(int64_t* pTstamp);

  //�������ָ�����ֽ�
  PdbErr_t SplitMost(NormalDataPage* pNewPage, int32_t bytes);

private:
  PdbErr_t UpdateIdxTs();
  PdbErr_t CleanUp();
  PdbErr_t InsertForPos(int idx, const uint8_t* pRec, size_t recLen);

private:
  PageHdr* pPage_;
};
