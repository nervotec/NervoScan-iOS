# NervoScan SDK for iOS

Welcome to the **NervoScan SDK**, a powerful Software Development Kit (SDK) designed for real-time physiological data scanning and analysis on iOS applications. 

---

## 📝 Overview

**The NervoScan SDK** is a powerful Software Development Kit (SDK) tailored for real-time
scanning and analysis of physiological data. Designed for IOS applications, it provides
functionalities to monitor vital signs and offer immediate feedback. Key features include:

### **Key Features**

1. **Heart Rate (HR)**
2. **Heart Rate Variability (HRV)**
   - Stress Level Classification
3. **Blood Pressure (BP)**
   - Systolic (SBP) and Diastolic (DBP)
   - Blood Pressure Classification
4. **Respiration Rate (RR)**
5. **SDNN**
6. **PNN50**
7. **RMSSD**
8. **Oxygen Saturation (SpO2)**
9. **Hemoglobin Levels**
10. **HbA1c** (Glycated Hemoglobin)
11. **Health Score**

### **How It Works**
- Utilizes the device camera for vital sign detection.
- Implements advanced signal processing and machine learning techniques.
- Includes robust error handling for accurate readings.
- Provides seamless real-time feedback.

### **Compatibility**
- **Supported Platforms:** iOS 13.0 and later
- **Programming Language:** Swift 
- **Integration:** Compatible with Swift Package Manager (SPM) and CocoaPods

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

### 2. Set Callbacks

The NervoScan SDK provides several callback methods to handle different stages and results during a scan. Developers can implement these methods to process data, update user interfaces, and handle errors effectively.

---

## 📖 Callback Methods

### **onCameraError**
**Purpose:** Handles errors related to camera access or permissions.

**Implementation Guidelines:**
- Notify the user about camera access issues.
- Provide instructions on enabling permissions.

```swift
func onCameraError() {
    DispatchQueue.main.async {
        self.alertMessage = "Camera Permission Denied. Please enable camera access in settings."
        self.showAlert = true
    }
}
```

### **onUpdateProgress**
**Purpose:** Provides real-time progress updates during the scanning process.

**Implementation Guidelines:**
- Update UI elements such as a progress bar.
- Display scan progress dynamically.

```swift
func onUpdateProgress(seconds: Float) {
    DispatchQueue.main.async {
        self.scanTime = seconds
        self.progressValue = seconds / 60
    }
}
```

### **onWindowResult**
**Purpose:** Processes real-time, window-level results.

**Implementation Guidelines:**
- Extract and update biometric parameters.
- Display real-time updates in the UI.

```swift
func onWindowResult(result: [String: Double]) {
    DispatchQueue.main.async {
        self.scanData = result
    }
}
```

### **onFullResult**
**Purpose:** Provides comprehensive scan results, including biometric values and classification results.

**Implementation Guidelines:**
- Parse and store full scan data.
- Use classification results for health analysis.

```swift
func onFullResult(result: [String: Double], classes: [String]) {
    DispatchQueue.main.async {
        self.averageScanData = result
        self.scanClasses = classes
    }
}
```

### **onMinResult**
**Purpose:** Outputs the minimum recorded biometric values.

**Implementation Guidelines:**
- Display minimum health metrics.
- Store values for historical tracking.

```swift
func onMinResult(result: [String: Double]) {
    DispatchQueue.main.async {
        self.minScanData = result
    }
}
```

### **onError**
**Purpose:** Handles errors encountered during the scanning process.

**Implementation Guidelines:**
- Display user-friendly error messages.
- Provide retry options or troubleshooting steps.

```swift
func onError(errorType: String, errorMessage: String) {
    DispatchQueue.main.async {
        self.alertMessage = errorMessage
        self.showAlert = true
    }
}
```

### **onFetchingFinished**
**Purpose:** Indicates completion of data fetching and transition to result processing.

**Implementation Guidelines:**
- Notify the user that processing is underway.
- Display a loading indicator if necessary.

```swift
func onFetchingFinished() {
    print("Fetching phase complete. Processing results now.")
}
```

### **onComplete**
**Purpose:** Signals the successful completion of the scan process.

**Implementation Guidelines:**
- Notify the user that the scan is complete.
- Save and process scan results.

```swift
func onComplete() {
    DispatchQueue.main.async {
        self.isCompleted = true
        print("Scan completed successfully.")
    }
}
```

---
Ensure you have a valid license key for testing.

### Sample App

This repository includes a sample app demonstrating SDK integration:

1. Clone the repository.
   Clone the repository:  
   ```swift
   git clone https://github.com/nervotec/NervoScanSampleIos.git
   ```
3. Open `NervoScanSample.xcodeproj`.
4. Add your valid license key to the sample app.
5. Run the app on a physical device for optimal results.

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
