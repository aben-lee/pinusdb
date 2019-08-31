#pragma once
#include "internal.h"
#include "port/os_file.h"
#include "commitlog/commit_log_file.h"

class CommitLogList
{
public:
  CommitLogList();
  ~CommitLogList();

  bool Init(const char* pLogPath, bool enableRep);

  PdbErr_t AppendData(uint64_t tabCrc, uint32_t fieldCrc,
    bool isRep, const CommitLogBlock* pLogBlock);

  void GetCurLogPos(uint64_t* pDataLogPos);
  void SetSyncPos(uint64_t syncPos);
  void SetRepPos(uint64_t repPos);

  PdbErr_t GetRedoData(uint64_t *pTabCrc, uint32_t *pFieldCrc,
    size_t* pRecCnt, size_t* pDataLen, uint8_t* pBuf);

  void Shutdown();

private:
  PdbErr_t InitLogFileList(const char* pLogPath);
  PdbErr_t NewLogFile();
  void AppendSyncInfo();

private:
  std::mutex logMutex_;
  bool enableRep_;             // �Ƿ������鸴��
  uint32_t nextFileCode_;      // ��һ���ļ����

  uint64_t redoPos_;            // �ָ�-λ��-����崻��ָ�����
  uint64_t repPos_;             // ����-λ��-���ڽ��ڴ�������д�����
  uint64_t syncPos_;            // ͬ��-λ��-�������������ݿ�ͬ��

  CommitLogFile* pRedoLog_;      // ����������־�ļ�
  CommitLogFile* pRepLog_;       // ����������־�ļ�
  CommitLogFile* pWriteLog_;     // д��־�ļ�
  std::string logPath_;        // ��־·��
  std::vector<CommitLogFile*> logFileVec_;  //��־�ļ��б�
};




