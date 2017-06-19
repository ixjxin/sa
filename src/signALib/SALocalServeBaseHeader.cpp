#include "SALocalServeBaseHeader.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
SALocalServeBaseHeader::SALocalServeBaseHeader():
    m_key(0)
  ,m_pid(0)
  ,m_type(-1)
{

}

uint SALocalServeBaseHeader::getSendedPid() const
{
    return m_pid;
}

void SALocalServeBaseHeader::setSendedPid(const uint &pid)
{
    m_pid = pid;
}

uint SALocalServeBaseHeader::getKey() const
{
    return m_key;
}

void SALocalServeBaseHeader::setKey(const uint &key)
{
    m_key = key;
}

int SALocalServeBaseHeader::getType() const
{
    return m_type;
}

void SALocalServeBaseHeader::setType(int type)
{
    m_type = type;
}

bool SALocalServeBaseHeader::fromXML(QXmlStreamReader* xml)
{
    while(!xml->atEnd() && !xml->hasError())
    {
        xml->readNext();
        if(xml->isStartElement())
        {
            if(xml->name() == SA_XML_LOCALSERVE_ROOT)
            {
                xml->readNext();
                if(xml->name() == SA_XML_LOCALSERVE_HEADER_KEY)
                {
                    m_key = xml->text().toUInt();
                }
                else if(xml->name() == SA_XML_LOCALSERVE_HEADER_TYPE)
                {
                    m_type = xml->text().toInt();
                }
                else if(xml->name() == SA_XML_LOCALSERVE_HEADER_PID)
                {
                    m_pid = xml->text().toInt();
                }
            }
        }
    }
}

QString SALocalServeBaseHeader::toXML() const
{
    QString str;
    QXmlStreamWriter xml(&str);
    initXmlStart(&xml);
    writeXMLHeader(&xml);
    xml.writeEndElement();
}

void SALocalServeBaseHeader::write(QDataStream &io) const
{
    io << *this;
}

void SALocalServeBaseHeader::read(QDataStream &io)
{
    io >> *this;
}
///
/// \brief 初始化xml，此时xml的节点位于<root>，最后要调用xml.writeEndElement();
/// \param xml
///
void SALocalServeBaseHeader::initXmlStart(QXmlStreamWriter *xml) const
{
    xml->setCodec("UTF-8");//设置编码
    xml->setAutoFormatting(true);//自动换行，否则会写成一坨不好看
    xml->setAutoFormattingIndent(2);//设置一个tab的空格数，也就是缩进量，一般是2或4
    xml->writeStartDocument();//写入xml文档头<?xml version="1.0" encoding="UTF-8"?>
    xml->writeStartElement(SA_XML_LOCALSERVE_ROOT);//每个start ele都要有write en
}

void SALocalServeBaseHeader::writeXMLHeader(QXmlStreamWriter *xml) const
{
    xml->writeStartElement(SA_XML_LOCALSERVE_HEADER);
    xml->writeTextElement(SA_XML_LOCALSERVE_HEADER_KEY,QString::number(m_key));
    xml->writeTextElement(SA_XML_LOCALSERVE_HEADER_TYPE,QString::number(m_type));
    xml->writeTextElement(SA_XML_LOCALSERVE_HEADER_PID,QString::number(m_pid));
    xml->writeEndElement();
}


//===========================================================

QDataStream &operator <<(QDataStream &io, const SALocalServeBaseHeader &d)
{
    io<<d.getKey()<<d.getSendedPid()<<d.getType();
    return io;
}

QDataStream &operator >>(QDataStream &io, SALocalServeBaseHeader &d)
{
    io >> d.m_key >> d.m_pid >> d.m_type;
    return io;
}
