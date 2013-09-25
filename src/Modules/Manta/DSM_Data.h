#ifndef DSM_Data_H
#define DSM_Data_H

namespace Manta
{
  class DSM_Data {
  public:
    virtual void getDatum(void *datum, size_t index) const = 0;
    virtual void getDatums(void *datums, size_t index, size_t num) const = 0;
    virtual ~DSM_Data() {}
  };
};
#endif
