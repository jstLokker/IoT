IoT เครื่องให้อาหารปลาตามเวลาที่เลือกไว้

คู่มือ

ติดตั้งอุปกรณ์ตาม https://wokwi.com/projects/421976042113852417

ไฟล์ Untitled-1 นำโค้ดลงในแอพ Arduino ลง Library ที่ต้องใช้ตามนี้
WiFi
ESPAsyncWebServer
time
HX711
Servo
Wire
Adafruit_SSD1306.h

บรรทัดที่ 9 และ 10 ให้เปลี่ยน เป็น ชื่อและรหัสWifi ที่อุปกรณ์จะเชื่อมต่อ (อุปกรณ์ต้องอยู่ในระยะสัญญาณ)

โหลดแอพในมือถือที่เป็นระบบ Android แอพ DroidScript

หลังอัพโหลดโค้ด และ บอร์ดเชื่อมกับwifiแล้ว ให้เปิดดู serial monitor 
serial monitor จะแสดง Ip address ของ wifi ขึ้นมา เช่น "192.168.1.154"

ไปที่แอพDroidScript กดสามจุด ขวาบน และกด New เขียนชื่อและกดOKจะได้หน้าแอพ กดค้างที่แอพที่สร้างมาใหม่  แล้วไปที่ Edit ลบทั้งหมดแล้วแทนที่ด้วยโค้ดของไฟล์ Untitled-2 มาลง 
และเปลี่ยน บรรทัดที่ 1 จาก "replace/" เป็น "http://ipที่ได้รับมาและปิดด้วย/" เช่น "http://192.168.1.154/"

!!โปรดอ่านให้ละเอียด มีคำถามติดต่อได้ที่ น้องตัง 4/2