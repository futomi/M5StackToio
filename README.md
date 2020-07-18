M5StackToio
===============

M5StackToio はソニー・インタラクティブエンタテインメント社の「[toio コア キューブ](https://toio.io/)」を操作するための [M5Stack](https://m5stack.com/) 用 Arduino ライブラリです。

---------------------------------------
## 目次

* [開発環境セットアップ](#Setup-IDE)
* [M5StackToio のインストール](#Install-M5StackToio)
* [スケッチ例](#Sketches)
* [メソッド](#Methods)
* [リリースノート](#Release-Note)
* [リファレンス](#References)
* [ライセンス](#License)

---------------------------------------
## <a id="Setup-IDE">開発環境セットアップ</a>

本ライブラリーを利用するにあたり M5Stack 開発環境が必要です。M5Stack の公式サイト (英語) に記載された手順に従って開発環境をセットアップしてください。

* [M5Stack Docs - Arduino IDE Development](https://docs.m5stack.com/#/en/arduino/arduino_development)

USB ドライバーのインストール、Arduino-IDE のインストール、Boards Manager の設定、ボードのインストール、ボードの選択、M5Stack Library のインストールが必要となります。

---------------------------------------
## <a id="Install-M5StackToio">M5StackToio のインストール</a>

本ページの右上の `Code` ボタンをクリックし `Download ZIP` を選択し、本ライブラリの zip ファイルをダウンロードしてください。

Arduino IDE を起動し、メニューバーの `スケッチ` -> `ライブラリをインクルード` -> `.ZIP形式のライブラリをインストール...` を選択してください。先ほどダウンロードした本ライブラリの zip ファイルを選択すると、本ライブラリのインストールが完了します。

---------------------------------------
## <a id="Sketches">スケッチ例</a>

本ライブラリのインストールが完了すると、Arduino IDE のメニューバーの `ファイル` -> `スケッチ例` の中から `M5StackToio` が選択できるようになります。この中には以下の 3 つのサンプルが用意されています。いずれも [M5Stack Basic](https://www.switch-science.com/catalog/3647/) および [M5Stack Gray](https://www.switch-science.com/catalog/3648/) で動作します。

### `basic`

本ライブラリが提供するメソッドを一通り実行するスケッチです。

事前に toio コア キューブ の電源を入れてください。

M5Stack が起動すると自動的に toio コア キューブ をスキャンします。toio コア キューブ が見つかると M5Stack の画面にデバイス名と MAC アドレスが表示されます。見つからなければ、再度、M5Stack ボタンのリセットボタンを押して再起動してください。

toio コア キューブ が発見されると、自動的に BLE 接続し、一連のメソッドを順次実行しながら M5Stack の画面に結果を表示します。

一連のメソッドの実行が完了すると、自動的に BLE 接続を切断して終了します。

### `event`

本ライブラリが提供するイベントをハンドリングするサンプルスケッチです。

事前に toio コア キューブ の電源を入れてください。

M5Stack が起動すると自動的に toio コア キューブ をスキャンします。toio コア キューブ が見つかると M5Stack の画面にデバイス名と MAC アドレスが表示されます。見つからなければ、再度、M5Stack ボタンのリセットボタンを押して再起動してください。

toio コア キューブ が発見された後、M5Stack の A ボタンを押すと toio コア キューブ と BLE 接続します。接続が完了すると、各種イベントを待ち受け、受信したイベント情報を M5Stack の画面に表示します。

### `joystick_drive`

[M5Stack用ジョイスティックユニット](https://www.switch-science.com/catalog/4050/)を使って toio コア キューブを運転するサンプルスケッチです。

 事前に toio コア キューブ の電源を入れてください。

M5Stack が起動すると自動的に toio コア キューブ をスキャンします。toio コア キューブ が見つかると M5Stack の画面にデバイス名と MAC アドレスが表示されます。見つからなければ、再度、M5Stack ボタンのリセットボタンを押して再起動してください。

toio コア キューブ と BLE 接続する前にジョイスティックをキャリブレーションする必要があります。M5Stack の画面上にジョイスティックの座標が表示されます。もし x と y の値が 0 でなければ、ジョイスティックの中心座標がずれています。M5Stack の C ボタンを押してキャリブレーションしてください。

toio コア キューブ が発見された後、M5Stack の A ボタンを押すと toio コア キューブ と BLE 接続します。接続が完了すると、ジョイスティックで toio コア キューブ を運転することができます。

BLE 接続中、ジョイスティックの z 軸を押すと、チャルメロが再生されます。また、M5Stack の B ボタンを押すと、toio コア キューブ の LED が白で点灯します。

[![joystick_drive のデモ](https://img.youtube.com/vi/FLccNi00Pds/0.jpg)](https://www.youtube.com/watch?v=FLccNi00Pds)

## <a id="Methods">メソッド</a>

**準備中**

前述のサンプルスケッチを参考にしてください。

---------------------------------------
## <a id="Release-Note">リリースノート</a>

* v1.0.0 (2020-07-19)
  * 初版リリース

---------------------------------------
## <a id="References">リファレンス</a>

* [toio 公式ページ](https://toio.io/)
* [toio コア キューブ 技術仕様](https://toio.github.io/toio-spec/)
* [M5Stack](https://m5stack.com/)
  * [ESP32 Basic Core IoT Development Kit](https://m5stack.com/collections/m5-core/products/basic-core-iot-development-kit)
  * [ESP32 GREY Development Kit with 9Axis Sensor](https://m5stack.com/collections/m5-core/products/grey-development-core)
  * [I2C Joystick Unit (MEGA328P)](https://m5stack.com/products/joystick-unit)
* [スイッチサイエンス](https://www.switch-science.com/)
  * [M5Stack Basic](https://www.switch-science.com/catalog/3647/)
  * [M5Stack Gray](https://www.switch-science.com/catalog/3648/)
  * [M5Stack用ジョイスティックユニット](https://www.switch-science.com/catalog/4050/)

---------------------------------------
## <a id="License">License</a>

The MIT License (MIT)

Copyright (c) 2020 Futomi Hatano

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
