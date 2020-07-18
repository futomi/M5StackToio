/* ----------------------------------------------------------------
  m5stack-toio - basic.ino

  Copyright (c) 2020 Futomi Hatano. All right reserved.
  https://github.com/futomi

  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  このサンプルスケッチは M5Stack Basic Core または GREY で動作します。

  [使い方]

  事前に Toio Core Cube の電源を入れてください。

  M5Stack が起動すると自動的に Toio Core Cube をスキャンします。
  Toio Core Cube が見つかると M5Stack の画面にデバイス名と MAC アドレス
  が表示されます。見つからなければ、再度、M5Stack ボタンのリセットボタンを
  押して再起動してください。

  Toio Core Cube が発見されると、自動的に BLE 接続し、一連のメソッドを
  順次実行しながら M5Stack の画面に結果を表示します。

  一連のメソッドの実行が完了すると、自動的に BLE 接続を切断して終了します。
  -------------------------------------------------------------- */
#include <M5Stack.h>
#include <Toio.h>

void displayProgressMessage(String msg, bool reset_cursor = true) {
  if (reset_cursor) {
    M5.Lcd.fillRect(0, 100, 320, 50, 0x000000);
    M5.Lcd.setCursor(0, 100, 2);
  }
  M5.Lcd.print(msg);
}

// Toio オブジェクト生成
Toio toio;

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Lcd.clear();

  // タイトル表示
  M5.Lcd.setCursor(85, 5, 4);
  M5.Lcd.print("M5StackToio");

  // 3 秒間 Toio Core Cube をスキャン
  M5.Lcd.setCursor(0, 50, 2);
  M5.Lcd.print("Scanning your toio core...");
  std::vector<ToioCore*> toiocore_list = toio.scan(3);

  // 見つからなければ終了
  size_t n = toiocore_list.size();
  if (n == 0) {
    M5.Lcd.setCursor(0, 50, 2);
    M5.Lcd.print("No toio Core Cube was found. Turn on your Toio Core Cube, then press the reset button of your Toio Core Cube.");
    return;
  }

  // 最初に見つかった Toio Core Cube の ToioCore オブジェクト
  ToioCore* toiocore = toiocore_list.at(0);
  M5.Lcd.setCursor(0, 50, 2);
  M5.Lcd.print("Your toio core was found:      ");

  // Toio Core のデバイス名と MAC アドレスを表示
  M5.Lcd.setCursor(0, 70, 2);
  M5.Lcd.print(String(toiocore->getName().c_str()) + " (" + String(toiocore->getAddress().c_str()) + ")");

  // BLE 接続開始
  displayProgressMessage("Connecting...");
  if (!toiocore->connect()) {
    displayProgressMessage("Failed to establish a BLE connection.", false);
    return;
  }
  displayProgressMessage("Connected.", false);
  delay(3000);

  // BLE プロトコルバージョンを取得
  displayProgressMessage("Getting the BLE protocol version... ");
  std::string ble_ver = toiocore->getBleProtocolVersion();
  displayProgressMessage(ble_ver.c_str(), false);
  delay(3000);

  // MIDI を再生 (チャルメラ)
  displayProgressMessage("Play a MIDI...");
  uint8_t charumera_data[39] = {
    3,             // Type of Sound control (MIDI)
    1,             // Repeat count
    12,            // Number of operations
    14,  69, 255,  // 140ms, A5
    14,  71, 255,  // 140ms, B5
    56,  73, 255,  // 560ms, C#6
    14,  71, 255,  // 140ms, B5
    14,  69, 255,  // 140ms, A5
    114, 128, 255, // no sound
    14,  69, 255,  // 140ms, A5
    14,  71, 255,  // 140ms, B5
    14,  73, 255,  // 560ms, C#6
    14,  71, 255,  // 140ms, B5
    14,  69, 255,  // 140ms, A5
    56,  71, 255   // 560ms, B5
  };
  toiocore->playSoundRaw(charumera_data, 39);
  delay(5000);

  // 効果音を再生 (11 パターン)
  displayProgressMessage("Play sound effects: Enter");
  toiocore->playSoundEffect(0);
  delay(3000);

  displayProgressMessage("Play sound effects: Selected");
  toiocore->playSoundEffect(1);
  delay(3000);

  displayProgressMessage("Play sound effects: Cancel");
  toiocore->playSoundEffect(2);
  delay(3000);

  displayProgressMessage("Play sound effects: Cursor");
  toiocore->playSoundEffect(3);
  delay(3000);

  displayProgressMessage("Play sound effects: Mat in");
  toiocore->playSoundEffect(4);
  delay(3000);

  displayProgressMessage("Play sound effects: Mat out");
  toiocore->playSoundEffect(5);
  delay(3000);

  displayProgressMessage("Play sound effects: Get 1");
  toiocore->playSoundEffect(6);
  delay(3000);

  displayProgressMessage("Play sound effects: Get 2");
  toiocore->playSoundEffect(7);
  delay(3000);

  displayProgressMessage("Play sound effects: Get 3");
  toiocore->playSoundEffect(8);
  delay(3000);

  displayProgressMessage("Play sound effects: Effect 1");
  toiocore->playSoundEffect(9);
  delay(3000);

  displayProgressMessage("Play sound effects: Effect 2");
  toiocore->playSoundEffect(10);
  delay(3000);

  // LED を黄色で点灯
  displayProgressMessage("Turn on the LED: yellow");
  toiocore->turnOnLed(0xff, 0xff, 0x00);
  delay(5000);

  // LED を消灯
  displayProgressMessage("Turn off the LED");
  toiocore->turnOffLed();
  delay(5000);

  // バッテリーレベルを取得
  displayProgressMessage("Getting the battery level...");
  uint8_t batt_level = toiocore->getBatteryLevel();
  displayProgressMessage(String(batt_level) + "%", false);
  delay(5000);

  // ボタン押下状態を取得
  displayProgressMessage("Getting the button state...");
  bool button_state = toiocore->getButtonState();
  displayProgressMessage(String(button_state), false);
  delay(5000);

  // モーションセンサーの状態を取得
  displayProgressMessage("Getting the state of the motion sensor... ");
  ToioCoreMotionData motion = toiocore->getMotion();
  displayProgressMessage(
    "flat=" + String(motion.flat) +
    ", clash=" + String(motion.clash) +
    ", dtap=" + String(motion.dtap) +
    ", attitude=" + String(motion.attitude), false);
  delay(5000);

  // 右に曲がりながら進む (左右のモーターを個別に制御)
  displayProgressMessage("Turning to the right...");
  toiocore->controlMotor(true, 50, true, 40);
  delay(5000);

  // 停止
  displayProgressMessage("Stopping...");
  toiocore->controlMotor(true, 0, true, 0);
  delay(5000);

  // 2 秒間だけ右に曲がりながら進む (左右のモーターを個別に制御)
  displayProgressMessage("Turning to the right for 2 seconds");
  toiocore->controlMotor(true, 40, true, 50, 2000);
  delay(5000);

  // BLE 切断
  toiocore->disconnect();
  M5.Lcd.setCursor(0, 90, 2);
  displayProgressMessage("Disconnected");
}

void loop() {

}
