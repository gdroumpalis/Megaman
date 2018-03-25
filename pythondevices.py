import usb.core
import usb.util
import array

dev = usb.core.find(idVendor=0x0403, idProduct=0x6001)
# print(device)

if dev is None:
    print("Device not found")

dev.set_configuration()

endpoint = dev[0][(0, 0)][0]


# data = dev.read(endpoint.bEndpointAddress,
#                            endpoint.wMaxPacketSize)
# #
# # RxData = ''.join([chr(x) for x in data])
# # print(RxData)

# print(endpoint)
# print(data)

# RxData = ''.join([chr(x) for x in data])
# print RxData

data = array.array('B', (0,)*4)
while True:
    try:
        data = dev.readline(endpoint.bEndpointAddress, endpoint.wMaxPacketSize)
        print(data)
    except usb.core.USBError as e:
        print(e)
        continue

