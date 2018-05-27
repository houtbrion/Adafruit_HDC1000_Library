
#include "Adafruit_HDC1000_U.h"

Adafruit_HDC1000_Unified::Adafruit_HDC1000_Unified(uint8_t type, int32_t tempSensorId, int32_t humiditySensorId, uint8_t addr):
	_hdc(type),
	_type(type),
	_temp(this, tempSensorId),
	_humidity(this, humiditySensorId),
	_addr(this,addr)
{}

boolean Adafruit_HDC1000_Unified::begin() {
	Wire.begin();
	return true;
}

void Adafruit_HDC1000_Unified::setName(sensor_t* sensor) {
	switch(_type) {
		case HDC1000:
			strncpy(sensor->name, HDC1000_NAME, sizeof(sensor->name)-1);
			break;
		case HDC1008:
			strncpy(sensor->name, HDC1008_NAME, sizeof(sensor->name)-1);
			break;
		case HDC1010:
			strncpy(sensor->name, HDC1010_NAME, sizeof(sensor->name)-1);
			break;
		case HDC1080:
			strncpy(sensor->name, HDC1080_NAME, sizeof(sensor->name)-1);
			break;
		case HDC2010:
			strncpy(sensor->name, HDC2010_NAME, sizeof(sensor->name)-1);
			break;
		default:
			strncpy(sensor->name, HDC1000_NAME, sizeof(sensor->name)-1);
	};
	sensor->name[sizeof(sensor->name)-1]=0;
}

void Adafruit_HDC1000_Unified::setMinDelay(sensor_t* sensor) {
	switch(_type) {
		case HDC1000:
			sensor->min_delay = HDC1000_MIN_DELAY;
			break;
		case HDC1008:
			sensor->min_delay = HDC1008_MIN_DELAY;
			break;
		case HDC1010:
			sensor->min_delay = HDC1010_MIN_DELAY;
			break;
		case HDC1080:
			sensor->min_delay = HDC1080_MIN_DELAY;
			break;
		case HDC2010:
			sensor->min_delay = HDC2010_MIN_DELAY;
			break;
		default:
			sensor->min_delay = HDC1000_MIN_DELAY;
	};
}

Adafruit_HDC1000_Unified::Temperature::Temperature(Adafruit_HDC1000_Unified* parent, int32_t id):
	_parent(parent),
	_id(id)
{}

bool Adafruit_HDC1000_Unified::Temperature::getEvent(sensors_event_t* event) {
	memset(event, 0, sizeof(sensors_event_t));
	event->version     = sizeof(sensors_event_t);
	event->sensor_id   = _id;
	event->type        = SENSOR_TYPE_AMBIENT_TEMPERATURE;
	event->timestamp   = millis();
	event->temperature = _parent->_hdc.readTemperature();
	return true;
}

void Adafruit_HDC1000_Unified::Temperature::getSensor(sensor_t* sensor) {
	memset(sensor, 0, sizeof(sensor_t));
	_parent->setName(sensor);
	sensor->version   = HDC1000U_DRIVER_VERSION;
	sensor->sensor_id = _id;
	sensor->type      = SENSOR_TYPE_AMBIENT_TEMPERATURE;
	_parent->setMinDelay(sensor);
	switch(_parent->_type) {
		case HDC1000:
			sensor->max_value  = HDC1000_TEMPERATURE_MAX_VALUE;
			sensor->min_value  = HDC1000_TEMPERATURE_MIN_VALUE;
			sensor->resolution = HDC1000_TEMPERATURE_RESOLUTION;
			break;
		case HDC1008:
			sensor->max_value  = HDC1008_TEMPERATURE_MAX_VALUE;
			sensor->min_value  = HDC1008_TEMPERATURE_MIN_VALUE;
			sensor->resolution = HDC1008_TEMPERATURE_RESOLUTION;
			break;
		case HDC1010:
			sensor->max_value  = HDC1010_TEMPERATURE_MAX_VALUE;
			sensor->min_value  = HDC1010_TEMPERATURE_MIN_VALUE;
			sensor->resolution = HDC1010_TEMPERATURE_RESOLUTION;
			break;
		case HDC1080:
			sensor->max_value  = HDC1080_TEMPERATURE_MAX_VALUE;
			sensor->min_value  = HDC1080_TEMPERATURE_MIN_VALUE;
			sensor->resolution = HDC1080_TEMPERATURE_RESOLUTION;
			break;
		case HDC2010:
			sensor->max_value  = HDC2010_TEMPERATURE_MAX_VALUE;
			sensor->min_value  = HDC2010_TEMPERATURE_MIN_VALUE;
			sensor->resolution = HDC2010_TEMPERATURE_RESOLUTION;
			break;
		default:
			sensor->max_value  = 0.0F;
			sensor->min_value  = 0.0F;
			sensor->resolution = 0.0F;
	}
}

Adafruit_HDC1000_Unified::Humidity::Humidity(Adafruit_HDC1000_Unified* parent, int32_t id):
	_parent(parent),
	_id(id)
{}

bool Adafruit_HDC1000_Unified::Humidity::getEvent(sensors_event_t* event){
	memset(event, 0, sizeof(sensors_event_t));
	event->version           = sizeof(sensors_event_t);
	event->sensor_id         = _id;
	event->type              = SENSOR_TYPE_RELATIVE_HUMIDITY;
	event->timestamp         = millis();
	event->relative_humidity = _parent->_hdc.readHumidity();
	return true;
}

void Adafruit_HDC1000_Unified::Humidity::getSensor(sensor_t* sensor) {
	memset(sensor, 0, sizeof(sensor_t));
	_parent->setName(sensor);
	sensor->version = HDC1000U_DRIVER_VERSION;
	sensor->sensor_id = _id;
	sensor->type = SENSOR_TYPE_RELATIVE_HUMIDITY;
	_parent->setMinDelay(sensor);
	switch(_parent->_type) {
		case HDC1000:
			sensor->max_value  = HDC1000_HUMIDITY_MAX_VALUE;
			sensor->min_value  = HDC1000_HUMIDITY_MIN_VALUE;
			sensor->resolution = HDC1000_HUMIDITY_RESOLUTION;
			break;
		case HDC1008:
			sensor->max_value  = HDC1008_HUMIDITY_MAX_VALUE;
			sensor->min_value  = HDC1008_HUMIDITY_MIN_VALUE;
			sensor->resolution = HDC1008_HUMIDITY_RESOLUTION;
			break;
		case HDC1010:
			sensor->max_value  = HDC1010_HUMIDITY_MAX_VALUE;
			sensor->min_value  = HDC1010_HUMIDITY_MIN_VALUE;
			sensor->resolution = HDC1010_HUMIDITY_RESOLUTION;
			break;
		case HDC1080:
			sensor->max_value  = HDC1080_HUMIDITY_MAX_VALUE;
			sensor->min_value  = HDC1080_HUMIDITY_MIN_VALUE;
			sensor->resolution = HDC1080_HUMIDITY_RESOLUTION;
			break;
		case HDC2010:
			sensor->max_value  = HDC2010_HUMIDITY_MAX_VALUE;
			sensor->min_value  = HDC2010_HUMIDITY_MIN_VALUE;
			sensor->resolution = HDC2010_HUMIDITY_RESOLUTION;
			break;
		default:
			sensor->max_value  = 0.0F;
			sensor->min_value  = 0.0F;
			sensor->resolution = 0.0F;
	}
}


