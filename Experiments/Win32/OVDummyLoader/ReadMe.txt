=========================================================================
    �����w�s�{�� : OVDummyLoader �M�׷��[
========================================================================


AppWizard �w�g���z�إߤF OVDummyLoader.dll�C

�o���ɮקt���c�� OVDummyLoader ���ε{�����C�@���ɮת����e�K�n�C

OVDummyLoader.vcproj
    �o�O�ϥ����ε{�����F�Ҳ��ͤ� VC++ �M�ת��D�n�M���ɡC
    ���t�����͸��ɮפ� Visual C++  ��������T�A�H�Φ����ϥ����ε{�����F�ҿ�������x�B�պA�M�M�ץ\�઺��T�C

OVDummyLoader.cpp
    �o�O�D�n DLL ��l�{���ɡC

proc.cpp
    �o���ɮקt���w�s�{�� xp_proc

/////////////////////////////////////////////////////////////////////////////
��L�з��ɮ�:

StdAfx.h, StdAfx.cpp
    �o���ɮ׬O�Ψӫظm�W�� OVDummyLoader.pch ������sĶ���Y (PCH) ��
    �M�W�� StdAfx.obj ������sĶ���O�ɡC


/////////////////////////////////////////////////////////////////////////////
��L�`�N�ƶ�:

�����o�Ӻ��F����A�нƻs OVDummyLoader.dll ��z�� SQL Server 
\Binn �ؿ��C

�q Visual Studio ��ƱM�סA�Ψϥ� SQL Server Enterprise Manager�A�ΰ���U�C SQL �R�O:
  sp_addextendedproc 'xp_proc', 'OVDummyLoader.DLL'
  �[�J�s�������w�s�{��

�z�i�H�ϥ� SQL �R�O:
  sp_dropextendedproc 'xp_proc'
  �Ө��������w�s�{��

�z�i�H�ϥ� SQL �R�O:
  DBCC xp_proc(FREE)
�q���A������ DLL (�R���Ψ��N�ɮ�) 


/////////////////////////////////////////////////////////////////////////////
