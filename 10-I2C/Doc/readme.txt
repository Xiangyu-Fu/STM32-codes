## I2C NOTES
### 寄存器位缩写 Abbreviations of Register Bits
ADDR: Address Send/Matched 	  地址已被发送/地址匹配
TxE:  Data Register Empty 	  数据寄存器为空
SB:   Start Bit 			  起始位
BTF:  Byte transfer finished  字节发送结束
PE:   Peripheral enable		  I2C模块使能


### EVENTs Descriptions
EV5:    SB = 1, 起始位
EV6:  ADDR = 1, 地址已被发送
EV8:   TxE = 1, 数据寄存器为空
EV8_2: TxE = 1, BTF = 1 数据寄存器为空, 字节发送结束

### Write Byte in EEPROM 单字节写入
@param (u8* pBuffer-->缓冲区指针, u8 WriteAddr-->EEPROM中的地址) 
1. 产生起始信号， 等待、检测并清除EV5事件 				--> I2C_GenerateSTART(I2Cx, ENABLE) 		& I2C_CheckEvent
2. 发送设备地址， 等待、检测并清除EV6事件				--> I2C_Send7bitAddress(I2Cx, adress, Mode) & I2C_CheckEvent
3. 发送要写入EEPROM的内部地址，等待、检测并清除EV8事件  	--> I2C_SendData(I2Cx, WriteAddr) 			& I2C_CheckEvent
4. 发送要写入EEPROM的数据， 	 等待、检测并清除EV8事件  	--> I2C_SendData(I2Cx, pBuffer) 			& I2C_CheckEvent
5. 发送停止信号										--> I2C_GenerateSTOP(I2Cx, ENABLE)

### Write Bytes in EEPROM 多字节写入
@param (u8* pBuffer, u8 WriteAdd, uint16_t NumByteToWrite -->写的字节数) 
1. 等待EEPROM准备完毕， 此处需要调用WaitEepromStandbyState函数
2. 调用单字节写入程序

#### WaitEepromStandbyState函数
1. 循环检测I2C的状态寄存器SR的地址已被发送ADDR位，1为发送成功
	- 发送起始信号
	- 读取SR寄存器
	- 向EEPROM发送地址
2. 清除AF(应答错误)位， 无应答置1
3. 发送停止信号

### EEPROM的页写入
@param (u8* pBuffer, u8 WriteAddr, uint16_t NumByteToWrite) 
1. 产生起始信号， 等待并检测EV5事件				--> I2C_GenerateSTART(I2Cx, ENABLE) 		& I2C_CheckEvent
2. 发送设备地址， 等待并检测EV6事件				--> I2C_Send7bitAddress(I2Cx, adress, Mode) & I2C_CheckEvent
3. 发送要写入EEPROM的内部地址，等待并检测EV8事件  	--> I2C_SendData(I2Cx, WriteAddr) 			& I2C_CheckEvent
4. 循环发送要写入EEPROM的数据，等待并检测EV8事件   	--> I2C_SendData(I2Cx, pBuffer) & pBuffer++	& I2C_CheckEvent
5. 发送停止信号并返回1							--> I2C_GenerateSTOP(I2Cx, ENABLE)

### I2C_EE_BufferWrite快速写入多字节函数
@param (u8* pBuffer, u8 WriteAddr, uint16_t NumByteToWrite) 
1. 计算整页和剩余字节数


### I2C_EE_BufferRead 读数据
@param (u8* pBuffer, u8 ReadAddr, uint16_t NumByteToRead-->读的字节数) 
1. 产生起始信号， 等待、检测并清除EV5事件 				--> I2C_GenerateSTART(I2Cx, ENABLE) 		& I2C_CheckEvent
2. 发送设备地址， 等待、检测并清除EV6事件				--> I2C_Send7bitAddress(I2Cx, adress, Mode) 
														& I2C_CheckEvent & I2C_Cmd(I2Cx, ENABLE)
4. 发送要读取EEPROM的内部地址，等待、检测并清除EV8事件  	--> I2C_SendData(I2Cx, WriteAddr) 			& I2C_CheckEvent
5. 产生第二次I2C起始信号， 等待、检测并清除EV5事件 		--> I2C_GenerateSTART(I2Cx, ENABLE) 		& I2C_CheckEvent
6. 发送设备地址， 等待、检测并清除EV6事件				--> I2C_Send7bitAddress(I2Cx, adress, Mode) & I2C_CheckEvent
7. 循环读取地址中的数据								--> while(NumByteToRead)
	- 若NumByteToRead == 1 发送非应答信号，结束传输	--> I2C_AcknowledgeConfig(I2Cx, DISABLE)   
														& I2C_GenerateSTOP(I2Cx, ENABLE)
	- 等待、检测并清除EV8事件 							--> I2C_CheckEvent 
	- 读取数据，指针自加，数据数自减					--> ReceiveData(I2Cx)
8. 使能应答											--> I2C_AcknowledgeConfig(I2Cx, DISABLE)

