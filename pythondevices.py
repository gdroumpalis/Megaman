import usb.core
import usb.util

dev = usb.core.find(idVendor=0x0403, idProduct=0x6001)
# print(device)

if  dev is None:
    print("Device not found")

dev.set_configuration()

endpoint = dev[0][(0,0)][0]


data = dev.read(endpoint.bEndpointAddress,
                           endpoint.wMaxPacketSize)
#
# RxData = ''.join([chr(x) for x in data])
# print(RxData)

print(endpoint)
print(data)
