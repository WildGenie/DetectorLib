#include "StdAfx.h"
#include "ITPDeCoderImpl.h"

ITPDeCoderImpl::ITPDeCoderImpl(void)
{
}

ITPDeCoderImpl::~ITPDeCoderImpl(void)
{
}
//get the len of the packet
int ITPDeCoderImpl::GetITPLen()
{
	WORD* len;
	len = (WORD*)m_Buf;
	return *len;
}
void ITPDeCoderImpl::Process ()
{
	//ITP
	//Packet header: 
	//  1: LowByte of Len
	//	2: HighByte of Len
	//	3: PacketType //0:For command 1: for image
	//	4: Reserve
	BYTE temp_buf [10240];
	//HEADER_LEN ==4,���Բ��ܴ���4.����һ�����䣬����Ĳ�����ͼ��
	while (m_End > HEADER_LEN)
	{
		int len = GetITPLen();
		ATLTRACE ("itp len is %d m_End in IPS is %d\n",len, m_End);
		if (m_End >= GetITPLen())
		{//One Packet Ready
			m_NextDeCoder->OnNotify(m_Buf+HEADER_LEN, len-HEADER_LEN);
			int left_len = m_End - len;//�൱�ڼ���ͷ��Ϣ������ͼ����Ϣ
			if(left_len)
			{
				//�൱�ڰ�ʣ�µ���Ϣ�ٷŵ�m_buf�У��ٽ���һ�εĴ���
				memcpy (temp_buf, m_Buf + len, left_len);
				memcpy (m_Buf, temp_buf, left_len);
			}
			m_End = left_len;
			ATLTRACE ("left len in IPS is %d\n", left_len);
		}
		else
		{
			m_NextDeCoder->OnNotify(m_Buf+HEADER_LEN,len-HEADER_LEN);
		}
	/*	else
			
			break;*/
	}
	
}