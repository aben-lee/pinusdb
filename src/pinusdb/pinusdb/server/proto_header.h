#pragma once

#include "internal.h"

#define METHOD_ERROR_REP               0x0         //���� �ظ�����
                                       
#define METHOD_CMD_LOGIN_REQ           0x010001    //��¼ ������
#define METHOD_CMD_LOGIN_REP           0x010002    //��¼ �ظ�����
                                       
#define METHOD_CMD_QUERY_REQ           0x010003    //��ѯ �����ģ�һ��ִ����䣩
#define METHOD_CMD_QUERY_REP           0x010004    //��ѯ �ظ����ģ������ظ�ִ�н���������ش����룩
                                       
#define METHOD_CMD_INSERT_REQ          0x010005    //���� �����ģ�һ�������ִ����䣩
#define METHOD_CMD_INSERT_REP          0x010006    //���� �ظ����ģ������ش����룩
                                       
#define METHOD_CMD_NONQUERY_REQ        0x010007    //ִ���������� �����ģ�һ��ִ����䣩
#define METHOD_CMD_NONQUERY_REP        0x010008    //ִ���������� �ظ����ģ��ظ�ִ�н����

#define METHOD_CMD_INSERT_TABLE_REQ   0x010009    //���� ������(�����Ƹ�ʽ)
#define METHOD_CMD_INSERT_TABLE_REP   0x01000A    //���� �ظ�����(�����Ƹ�ʽ)

/*
** |------4-----|------4-----|------4-----|------4-----|
** |   Version  |   Method   |  BodyLen   | ReturnVal  |
** |---------------------------------------------------|
** |  fieldCnt  |    recCnt  |  errPos    |            |
** |---------------------------------------------------|
** |            |            |            |            |
** |---------------------------------------------------|
** |            |            |  BodyCrc   |  HeadCrc   |
** |---------------------------------------------------|
**/
class ProtoHeader
{
public:
  ProtoHeader();
  ~ProtoHeader();

  void Load(uint8_t* pHead);

  uint32_t GetVersion();
  uint32_t GetMethod();
  uint32_t GetBodyLen();
  uint32_t GetReturnVal();
  uint32_t GetFieldCnt();
  uint32_t GetRecordCnt();
  uint32_t GetErrPos();
  uint32_t GetBodyCrc();
  uint32_t GetHeadCrc();

  void SetVersion(uint32_t version);
  void SetMethod(uint32_t methodId);
  void SetBodyLen(uint32_t bodyLen);
  void SetReturnVal(uint32_t retVal);
  void SetRecordCnt(uint32_t recordCnt);
  void SetFieldCnt(uint32_t fieldCnt);
  void SetErrPos(uint32_t errPos);
  void SetBodyCrc(uint32_t bodyCrc);

  void UpdateHeadCrc();

  void InitHeader(int32_t methodId, int32_t bodyLen, int32_t retVal, int32_t bodyCrc);

  enum {
    kProtoHeadCalcCrcLen = 60,    //CRC����60�ֽ�
    kProtoHeadLength = 64,        //����ͷ64�ֽ�
    kProtoVersion = 0x00010000,   //Э��汾��
  };

private:
  uint8_t* pHead_;
};
