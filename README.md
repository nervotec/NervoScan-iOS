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
- **Xcode Version:** Xcode 16.0 or later
- **Language:** Swift 6.0 or later

---

## 🚀 Installation

# Swift Package Manager (SPM) Integration

Easily add the **NervoScan SDK** and **LicenseSpring SDK** to your project using Swift Package Manager (SPM).

## Step 1: Open Xcode and Add Packages
1. Open **Xcode** and go to **File > Add Packages**.
2. Enter the following repository URLs:

   - **NervoScan SDK**:  
     ```
     https://github.com/nervotec/NervoScan-iOS
     ```
   - **LicenseSpring SDK**:  
     ```
     https://github.com/licensespringios/licensespring
     ```

## Step 2: Choose Versions
3. For each package, select the **desired version or branch** (e.g., `main` or a specific tagged release).

## Step 3: Add to Target
4. Make sure both packages are added to your **Xcode target**.

## Step 4: Verify Integration
5. Go to **Project Navigator** → **Package Dependencies** and confirm that `NervoScanSDK` and `LicenseSpring` appear in the package list.
6. **Build your project** (`Cmd + B`) to ensure the dependencies are correctly integrated.

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

#### Sample Integration

```swift
import NervoScanSDK
import SwiftUI

struct ContentView: View, NervoScanCallback {
    
    @State private var session: AVCaptureSession?
    @State private var spo2: String = "N/A"
    @State private var hr: String = "N/A"
    @State private var rr: String = "N/A"
    @State private var isScanning: Bool = false

    private var nervoScanSdk: NervoScanSdk?

    init() {
        nervoScanSdk = NervoScanSdk(licenseKey: "YOUR_LICENSE_KEY ")
    }

    private func initializeCameraSession() {
        nervoScanSdk?.initializeCameraManager()
        session = nervoScanSdk?.getCameraSession()
        if session == nil {
            alertMessage = "Failed to initialize camera session."
            showAlert = true
        }
    }

    var body: some View {
        VStack {
            if let session = session {
                CameraPreview(session: session)
                    .frame(height: 300)
                    .cornerRadius(10)
                    .padding()
            } else {
                Text("Camera session not available.")
                    .foregroundColor(.red)
            }

            Spacer()

            if isScanning {
                Text("Scanning...")
                    .font(.headline)
                    .foregroundColor(.blue)
                    .padding()
            }
            Button(action: {
                if isScanning {
                    stopScan()
                } else {
                    startScan()
                }
            }) {
                Text(isScanning ? "Stop Scan" : "Start Scan")
                    .font(.headline)
                    .padding()
                    .frame(maxWidth: .infinity)
                    .background(isScanning ? Color.red : Color.green)
                    .foregroundColor(.white)
                    .cornerRadius(10)
                    .padding(.horizontal)
            }
        }
        .padding()
        .onAppear {
            initializeCameraSession()
            startScan()
        }
        .onDisappear {
            stopScan()
        }
    }
}

```
#### Sample Integration CameraPreview

```swift
import AVFoundation
struct CameraPreview: UIViewRepresentable {
    let session: AVCaptureSession

    func makeUIView(context: Context) -> VideoPreviewView {
        let view = VideoPreviewView()
        view.videoPreviewLayer.session = session
        view.videoPreviewLayer.videoGravity = .resizeAspectFill
        view.videoPreviewLayer.connection?.videoOrientation = .portrait
        return view
    }

    func updateUIView(_ uiView: VideoPreviewView, context: Context) {
        // No dynamic updates required for this view.
    }

    class VideoPreviewView: UIView {
        override class var layerClass: AnyClass {
            AVCaptureVideoPreviewLayer.self
        }

        var videoPreviewLayer: AVCaptureVideoPreviewLayer {
            return layer as! AVCaptureVideoPreviewLayer
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
- Ensure result contains biometric parameters as a dictionary of type [String: Double].

```swift
func onWindowResult(result: [String: Double]) {
    print("Testing onWindow Results:")
    for (key, value) in result {
        print("\(key): \(value)")
    }
}
```

### **onFullResult**
**Purpose:** Provides comprehensive scan results, including biometric values and classification results.

**Implementation Guidelines:**
- Parse and store full scan data.
- Use classification results for health analysis.
- Ensure result contains biometric parameters as a dictionary of type [String: Double].
- Utilize the classes: [String] array for classification labels:
     - classes[0] → Stress Level (e.g., "Low Stress", "High Stress")
     - classes[1] → Blood Pressure Level (e.g., "Normal BP", "Hypertension")

```swift
func onFullResult(result: [String: Double], classes: [String]) {
    DispatchQueue.main.async {
        for (key, value) in result {
            let intValue: Int
            if value > Double(Int.max) {
                intValue = Int.max
            } else if value < Double(Int.min) {
                intValue = Int.min
            } else {
                intValue = Int(value)
            }

            // ✅ Directly Print Values
            switch key {
            case "SPO2":
                let spo2Value = String(format: "%.0f", round(value * 100))
                print("SPO2: \(spo2Value)")
            case "HR":
                print("HR: \(intValue)")
            case "RR":
                print("RR: \(intValue)")
            case "SDNN":
                print("SDNN: \(intValue)")
            case "RMSSD":
                print("RMSSD: \(intValue)")
            case "PNN50":
                print("PNN50: \(intValue)")
            case "SBP":
                print("SBP: \(intValue)")
            case "DBP":
                print("DBP: \(intValue)")
            case "Glucose":
                let glucoseValue = String(format: "%.2f", value)
                print("Glucose: \(glucoseValue)")
            case "Hemo":
                let hemoValue = String(format: "%.2f", value)
                print("Hemo: \(hemoValue)")
            case "RGBHR":
                print("RGBHR: \(intValue)")
            case "HealthScore":
                print("HealthScore: \(value)")
            default:
                break
            }
        }
        // ✅ Print Classification Labels (Stress Level & BP Level)
        if classes.indices.contains(0) {
            print("Stress Level: \(classes[0])")
        }
        if classes.indices.contains(1) {
            print("Blood Pressure Level: \(classes[1])")
        }
        
    }
}

```

### **onMinResult**
**Purpose:** Outputs the minimum recorded biometric values.

**Implementation Guidelines:**
- Display minimum health metrics.
- Store values for historical tracking.
- Ensure result contains biometric parameters as a dictionary of type [String: Double].

```swift
func onMinResult(result: [String: Double]) {
       print("Testing onWindow Results:")
        for (key, value) in result {
        print("\(key): \(value)")
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
- **Framework Not Found: Check if the framework is correctly added:
   
    Go to General > Frameworks, Libraries, and Embedded Content.
    Verify that NervoScanSDK appears in the list.
    If missing, click + and add NervoScanSDK.framework.
    Ensure the Embed option is set to Embed & Sign.
    Clean and rebuild the project
    
### Known Limitations

- **Simulator Support:** Camera functionality is unavailable on the iOS Simulator. Use a physical device.

---

## 🤝 Contributing

We welcome contributions to the NervoScan SDK. Please follow our [contribution guide](#) for detailed instructions.

---

## 📜 License

The NervoScan SDK is a **paid product** governed by the licensing agreement provided upon purchase. The source code is proprietary.

---
