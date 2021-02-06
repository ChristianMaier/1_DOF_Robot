#ifndef _ROS_SERVICE_pos_service_h
#define _ROS_SERVICE_pos_service_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace ros_control_example
{

static const char POS_SERVICE[] = "ros_control_example/pos_service";

  class pos_serviceRequest : public ros::Msg
  {
    public:
      typedef float _dummy_type;
      _dummy_type dummy;

    pos_serviceRequest():
      dummy(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_dummy;
      u_dummy.real = this->dummy;
      *(outbuffer + offset + 0) = (u_dummy.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dummy.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_dummy.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_dummy.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->dummy);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_dummy;
      u_dummy.base = 0;
      u_dummy.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dummy.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_dummy.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_dummy.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->dummy = u_dummy.real;
      offset += sizeof(this->dummy);
     return offset;
    }

    virtual const char * getType() override { return POS_SERVICE; };
    virtual const char * getMD5() override { return "6a9e84a80748148b6fd9b4f02558ea76"; };

  };

  class pos_serviceResponse : public ros::Msg
  {
    public:
      typedef float _pos_type;
      _pos_type pos;

    pos_serviceResponse():
      pos(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_pos;
      u_pos.real = this->pos;
      *(outbuffer + offset + 0) = (u_pos.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pos.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pos.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pos.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pos);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_pos;
      u_pos.base = 0;
      u_pos.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pos.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pos.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pos.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pos = u_pos.real;
      offset += sizeof(this->pos);
     return offset;
    }

    virtual const char * getType() override { return POS_SERVICE; };
    virtual const char * getMD5() override { return "b6fb6507bc71350dd1c10d16c76b741e"; };

  };

  class pos_service {
    public:
    typedef pos_serviceRequest Request;
    typedef pos_serviceResponse Response;
  };

}
#endif
