// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "NervoScanSDK",
    platforms: [
        .iOS(.v14) // Specify the minimum iOS version required
    ],
    products: [
        .library(
            name: "NervoScanSDK",
            targets: ["NervoScanSDK"]
        ),
    ],
    targets: [
        .binaryTarget(
            name: "NervoScanSDK",
            path: "./NervoScanSDK.xcframework"
        ),
    ]
)

