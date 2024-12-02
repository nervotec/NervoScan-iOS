# NervoScan SDK for iOS

Welcome to the **NervoScan SDK**, a comprehensive solution for integrating real-time health monitoring features into your iOS applications.

---

## 📝 Overview

The NervoScan SDK provides cutting-edge real-time health monitoring capabilities, including:

- **SPO2 (Oxygen Saturation)**
- **Heart Rate (HR)**
- **Respiratory Rate (RR)**
- **Heart Rate Variability (HRV)**
- **Stress Level**
- **Blood Pressure**
- **HbA1C (Glycated Hemoglobin)**
- **Hemoglobin Levels**
- **Health Score**

Perfect for health and fitness apps, the SDK is designed for seamless integration, efficient algorithms, and reliable results.

👉 Visit our [official website](https://nervotec.com) for more details.

---

## ⚙️ System Requirements

- **iOS Version:** iOS 13.0 or later
- **Xcode Version:** Xcode 15.0 or later
- **Language:** Swift 5.0 or later

---

## 🚀 Installation

### Swift Package Manager (SPM)

Easily add the NervoScan SDK to your project:

1. Open Xcode and go to **File > Add Packages**.
2. Enter the repository URL:
   ```
   https://github.com/nervotec/NervoScan-iOS
   ```
3. Choose the desired version or branch (e.g., `main` or a tagged release).
4. Add the package to your target.

---

## 🔑 Licensing

The NervoScan SDK requires a valid license key. To obtain one, contact us at **sales@nervoscan.com**.

### Adding the License Key

Initialize the SDK with your license key:

```swift
let nervoScanSdk = NervoScanSdk(licenseKey: "YOUR_LICENSE_KEY")
```

---

## 📖 Usage

### 1. Initialize and Configure the SDK

Ensure your app requests camera access by updating the `Info.plist` file:

```xml
<key>NSCameraUsageDescription</key>
<string>We need camera access for health monitoring.</string>
```

### 2. Using the SDK

#### Set Up the ViewModel

The `CameraViewModel` manages the SDK’s functionality and camera session.

```swift
import SwiftUI

@StateObject private var viewModel = CameraViewModel()

var body: some View {
    VStack {
        if let session = viewModel.session {
            CameraPreview(session: session)
        }
        Button("Start Scan") {
            viewModel.startScan()
        }
    }
}
```

#### Sample Integration

```swift
import SwiftUI
import NervoScanSDK

struct ScanView: View {
    @StateObject private var viewModel = CameraViewModel()

    var body: some View {
        VStack {
            if let session = viewModel.session {
                CameraPreview(session: session)
            } else {
                Text("Camera session not available.")
            }
            Button(viewModel.isScanning ? "Stop Scan" : "Start Scan") {
                if viewModel.isScanning {
                    viewModel.stopScan()
                } else {
                    viewModel.startScan()
                }
            }
        }
        .onAppear {
            viewModel.startScan()
        }
        .onDisappear {
            viewModel.stopScan()
        }
    }
}
```

---

## 🛠️ Testing

### Unit Tests

Run unit tests:

1. Select the test scheme in Xcode.
2. Press `Command+U`.

Ensure you have a valid license key for testing.

### Sample App

The repository includes a sample app demonstrating SDK integration:

1. Clone the repository.
2. Open `NervoScanSample.xcodeproj`.
3. Add your valid license key to the sample app.
4. Run the app on a physical device for optimal results.

---

## 🔧 Troubleshooting

### Common Issues

- **Invalid License Key:** Ensure the license key matches your registered account.
- **Camera Access Denied:** Verify app permissions in **Settings > Privacy > Camera**.
- **Installation Issues:** Ensure your Xcode project targets iOS 13.0 or later.

### Known Limitations

- **Simulator Support:** Camera functionality is unavailable on the iOS Simulator. Use a physical device.
- **watchOS and visionOS:** Limited support. Contributions are welcome.

---

## 🤝 Contributing

We welcome contributions to the NervoScan SDK. Please follow our [contribution guide](#) for detailed instructions.

---

## 📜 License

The NervoScan SDK is a **paid product** governed by the licensing agreement provided upon purchase. The source code is proprietary.

---
