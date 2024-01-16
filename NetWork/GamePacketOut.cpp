#include "StdAfx.h"
#include ".\gamepacketout.h"

GamePacketOut::GamePacketOut(void)
{
}

GamePacketOut::GamePacketOut(int Code)
{
	
	m_offset=0;
	WriteByte(0x00);//No fragments
	WriteByte(PACKET_TYPE_MESSAGE);//Simple Message
	WriteShort(0x00);//Reserved for PacketSize
	WriteInversedInt(0x00);//Packet ID
	WriteInversedInt(0x00);//Packet MasterID
	WriteShort(0x00);//Data Key
	WriteShort(0x00);//Checksum
	WriteShort(Code);
}

GamePacketOut::~GamePacketOut(void)
{

}

void GamePacketOut::WritePacketID(int id)
{
	m_buff[4]=(BYTE)(id);
	m_buff[5]=(BYTE)(id >> 8);
	m_buff[6]=(BYTE)(id >> 16);
	m_buff[7]=(BYTE)(id >> 24);
}

void GamePacketOut::WritePacketMasterID(int masterID)
{
	m_buff[8]=((masterID & 0xffff) & 0xff);
	m_buff[9]=((masterID & 0xffff) >> 8);
	m_buff[10]=((masterID >> 16) & 0xff);
	m_buff[11]=(masterID >> 24);
}


void GamePacketOut::Encode(short KeyStart)
{
	m_buff[12]=(KeyStart & 0xff);
	m_buff[13]=((KeyStart >> 8) & 0xff);

	unsigned short ushCleeTmp=KeyStart;
	
	for (int i=16; i<m_offset; i++)
	{
		ushCleeTmp=(ushCleeTmp*PACKET_CRYPT_KEY)+1;
		m_buff[i] ^= ushCleeTmp;
	}
}

void GamePacketOut::WriteChecksum()
{
	short val = 0;
	for (int i=16;i<m_offset;i++)
	{

		val+=m_buff[i];
	}

	m_buff[14]=(char)(val & 0xff);
	m_buff[15]=(char)(val >> 8);
}

void GamePacketOut::WriteLen()
{
	m_buff[2]=(m_offset & 0xff);
	m_buff[3]=((m_offset >> 8) & 0xff);
}

int GamePacketOut::GetID()
{
	return (int)(((m_buff[7]) << 24) | ((m_buff[6]) << 16) | ((m_buff[5]) << 8) | m_buff[4]);
}

void GamePacketOut::FinishPacket(ClientBase	*Client)
{
	m_client=Client;
	memcpy(&m_sockaddr,&Client->GetAddrSock(),sizeof(SOCKADDR_IN));
	Encode((short)0x142);
	WriteChecksum();
	WriteLen();
}

