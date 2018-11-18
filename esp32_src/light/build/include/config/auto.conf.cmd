deps_config := \
	/home/jdwl/ESP32/IDF/esp-idf/components/app_trace/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/aws_iot/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/bt/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/driver/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/esp32/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/esp_adc_cal/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/ethernet/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/fatfs/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/freertos/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/heap/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/libsodium/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/log/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/lwip/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/mbedtls/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/openssl/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/pthread/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/spi_flash/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/spiffs/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/tcpip_adapter/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/wear_levelling/Kconfig \
	/home/jdwl/ESP32/IDF/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/jdwl/ESP32/IDF/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/jdwl/ESP32/IDF/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/jdwl/ESP32/IDF/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
