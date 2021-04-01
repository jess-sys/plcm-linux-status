.PHONY=install

build:
	cd plcm/plcm_drv_v013 && make
	cd ../plcm_message && make
	cd ../../	

install:
	sudo cp plcm_ip /bin && chmod +x /bin/plcm_ip
	sudo cp plcm_screen /bin && chmod +x /bin/plcm_screen
	sudo cp plcm/plcm_message /bin && chmod +x plcm_message
	sudo cp plcm/plcm_drv_v013/plcm_drv.ko /lib/modules/$(shell uname -r)/kernel/drivers
	echo 'mymodule' | sudo tee -a /etc/modules
	sudo depmod
