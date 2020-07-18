/* ----------------------------------------------------------------
  m5stack-toio - event.ino

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

  Toio Core Cube が発見された後、M5Stack の A ボタンを押すと Toio Core
  Cube と BLE 接続します。接続が完了すると、各種イベントを待ち受け、受信し
  たイベント情報を M5Stack の画面に表示します。
  -------------------------------------------------------------- */
#include <M5Stack.h>
#include <Toio.h>

void displayCaptionButtonA(String caption) {
  M5.Lcd.fillRect(30, 215, 120, 20, 0x000000);
  M5.Lcd.setCursor(30, 215, 2);
  M5.Lcd.print("[" + caption + "]");
}

// Toio オブジェクト生成
Toio toio;

// 発見された ToioCore オブジェクトのポインタ変数を定義
ToioCore* toiocore;

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
  toiocore = toiocore_list.at(0);
  M5.Lcd.setCursor(0, 50, 2);
  M5.Lcd.print("Your toio core was found:");

  // Toio　Core のデバイス名と MAC アドレスを表示
  M5.Lcd.setCursor(0, 70, 2);
  M5.Lcd.print(String(toiocore->getName().c_str()) + " (" + String(toiocore->getAddress().c_str()) + ")");

  // M5Stack のボタン A のキャプションを表示
  displayCaptionButtonA(" Connect  ");

  // イベント情報表示
  M5.Lcd.setCursor(0, 100, 2);
  M5.Lcd.print("- Connection");
  M5.Lcd.setCursor(90, 100, 2);
  M5.Lcd.print(":");

  M5.Lcd.setCursor(0, 120, 2);
  M5.Lcd.print("- Button");
  M5.Lcd.setCursor(90, 120, 2);
  M5.Lcd.print(":");

  M5.Lcd.setCursor(0, 140, 2);
  M5.Lcd.print("- Battery");
  M5.Lcd.setCursor(90, 140, 2);
  M5.Lcd.print(":");

  M5.Lcd.setCursor(0, 160, 2);
  M5.Lcd.print("- Motion");
  M5.Lcd.setCursor(90, 160, 2);
  M5.Lcd.print(":");

  // Connection イベントのコールバックをセット
  toiocore->onConnection([](bool state) {
    M5.Lcd.setCursor(100, 100, 2);
    M5.Lcd.print(state ? "Connected   " : "Disconnected");
    displayCaptionButtonA(state ? "Disconnect" : " Connect  ");
  });

  // Button イベントのコールバックをセット
  toiocore->onButton([](bool state) {
    M5.Lcd.setCursor(100, 120, 2);
    M5.Lcd.print(state ? "Pressed " : "Released");
  });

  // Battery イベントのコールバックをセット
  toiocore->onBattery([](uint8_t level) {
    M5.Lcd.setCursor(100, 140, 2);
    M5.Lcd.print(String(level) + " %  ");
  });

  // Motion イベントのコールバックをセット
  toiocore->onMotion([](ToioCoreMotionData motion) {
    M5.Lcd.setCursor(100, 160, 2);
    M5.Lcd.print("flat=" + String(motion.flat) + ", clash=" + String(motion.clash) + ", dtap=" + String(motion.dtap) + ", attitude=" + String(motion.attitude));
  });
}

void loop() {
  M5.update();

  // イベントを扱う場合は、必ずここで Toio オブジェクトの
  // loop() メソッドを呼び出すこと
  toio.loop();

  // M5Stack のボタン A が押されたときの処理
  if (M5.BtnA.wasReleased()) {
    // Toio Core Cube と BLE 接続中かどうかをチェック
    if (toiocore->isConnected()) {
      toiocore->disconnect(); // 接続中なら切断
    } else {
      toiocore->connect(); // 切断中なら接続
    }
  }
}
