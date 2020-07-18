/* ----------------------------------------------------------------
  ToioCore.h

  Copyright (c) 2020 Futomi Hatano. All right reserved.
  https://github.com/futomi

  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
  -------------------------------------------------------------- */
#ifndef ToioCore_h
#define ToioCore_h

#include <Arduino.h>
#include <string>
#include <functional>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

struct ToioCoreMotionData {
  bool flat;
  bool clash;
  bool dtap;
  uint8_t attitude;
};

typedef std::function<void(bool connected)> OnConnectionCallback;
typedef std::function<void(bool state)> OnButtonCallback;
typedef std::function<void(uint8_t level)> OnBatteryCallback;
typedef std::function<void(ToioCoreMotionData motion)> OnMotionCallback;

// ---------------------------------------------------------------
// ToioCore クラス
// ---------------------------------------------------------------
class ToioCore {
  private:
    const char* _TOIO_SERVICE_UUID     = "10b20100-5b3b-4571-9508-cf3efcd7bbae";
    const char* _TOIO_CHAR_UUID_BATT   = "10b20108-5b3b-4571-9508-cf3efcd7bbae";
    const char* _TOIO_CHAR_UUID_LIGHT  = "10b20103-5b3b-4571-9508-cf3efcd7bbae";
    const char* _TOIO_CHAR_UUID_SOUND  = "10b20104-5b3b-4571-9508-cf3efcd7bbae";
    const char* _TOIO_CHAR_UUID_BUTTON = "10b20107-5b3b-4571-9508-cf3efcd7bbae";
    const char* _TOIO_CHAR_UUID_MOTION = "10b20106-5b3b-4571-9508-cf3efcd7bbae";
    const char* _TOIO_CHAR_UUID_CONF   = "10b201ff-5b3b-4571-9508-cf3efcd7bbae";
    const char* _TOIO_CHAR_UUID_MOTOR  = "10b20102-5b3b-4571-9508-cf3efcd7bbae";

    BLEAdvertisedDevice* _device;
    BLEClient* _client;

    BLERemoteCharacteristic* _char_battery;
    BLERemoteCharacteristic* _char_light;
    BLERemoteCharacteristic* _char_sound;
    BLERemoteCharacteristic* _char_button;
    BLERemoteCharacteristic* _char_motion;
    BLERemoteCharacteristic* _char_conf;
    BLERemoteCharacteristic* _char_motor;

    OnConnectionCallback _onconnection;
    OnButtonCallback _onbutton;
    OnBatteryCallback _onbattery;
    OnMotionCallback _onmotion;

  private:
    void _wait(const unsigned long msec);

  public:
    // コンストラクタ
    ToioCore(BLEAdvertisedDevice& device);

    // デストラクタ
    ~ToioCore();

    // アドレスを取得
    std::string getAddress();

    // デバイス名を取得
    std::string getName();

    // 接続
    bool connect();

    // 切断
    void disconnect();

    // 接続状態を返す
    bool isConnected();

    // 接続状態イベントのコールバックをセット
    void onConnection(OnConnectionCallback cb);

    // サウンド再生開始 (生データ指定)
    void playSoundRaw(uint8_t* data, size_t length);

    // サウンド再生開始 (効果音)
    void playSoundEffect(uint8_t sound_id, uint8_t volume = 0xff);

    // サウンド再生停止
    void stopSound();

    // LED 点灯
    void turnOnLed(uint8_t r, uint8_t g, uint8_t b);

    // LED 消灯
    void turnOffLed();

    // バッテリーレベルを取得
    uint8_t getBatteryLevel();

    // バッテリーイベントのコールバックをセット
    void onBattery(OnBatteryCallback cb);

    // ボタンの状態を取得
    bool getButtonState();

    // ボタンイベントのコールバックをセット
    void onButton(OnButtonCallback cb);

    // モーションセンサーの状態を取得
    ToioCoreMotionData getMotion();

    // モーションセンサーのコールバックをセット
    void onMotion(OnMotionCallback cb);

    // BLE プロトコルバージョン取得
    std::string getBleProtocolVersion();

    // 水平検出のしきい値設定
    void setFlatThreshold(uint8_t deg = 45);

    // 衝突検出のしきい値設定
    void setClashThreshold(uint8_t level = 7);

    // ダブルタップ検出の時間間隔の設定
    void setDtapThreshold(uint8_t level = 5);

    // モーター制御 (引数の値をそのまま送信するローレベルのメソッド)
    void controlMotor(bool ldir, uint8_t lspeed, bool rdir, uint8_t rspeed, uint16_t duration = 0);

    // 運転 (モーター制御をスロットルとステアリング操作に置き換える)
    void drive(int8_t throttle, int8_t steering);

    // Toio.cpp から呼ばれる (.ino からは直接呼ばない)
    void _loop();
};

#endif
