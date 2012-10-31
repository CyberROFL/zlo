#include <utils/instance/zlo_instance.hpp>

#include <OpcEnum.h>
#include <opcda.h>

namespace zlo {
namespace opc {

typedef utils::instance< IOPCServerList > enum_instance;
typedef utils::instance<   IOPCServer   > server_instance;

} // namespace opc
} // namespace zlo
