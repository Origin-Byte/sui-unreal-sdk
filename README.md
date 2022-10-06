# sui-unreal-sdk

Connecting Unreal game developers to Sui blockchain and Origin Byte's NFT ecosystem.

# Features
- For Rpc clients’ direct interaction with the Sui JSON-RPC https://docs.sui.io/sui-jsonrpc
	- Get SUI objects
	- Call Sui Move contracts
	- Sign, Batch and Execute Transactions,
	- Transfer, Split and Merge SUI coins and objects
	- Get Historical Event Data
- Restore Ed25519 Keypairs from BIP39 mnemonics and Create new Keypairs
- Tested on Windows desktop with Sui version 0.10.0
- Works with Unreal Engine 5

# Getting Started
## Quickstart: download this repository and open with Unreal Engine 5
Check the Sample Level and the Blueprint Nodes in the Level Blueprint.
The SuiUnrealSDKCore module contains all the high level functionalities. Both C++ and Blueprints are supported.

## How to use it in your project
Install [VaRest](https://www.unrealengine.com/marketplace/en-US/product/varest-plugin) Plugin from the Marketplace, and copy all plugins found in the Plugins folder (Bip39UE, LibsodiumUE, SuiUnrealSDKCore )

## Notice
Because of the limitations of Blueprints, sui JSON API method signatures use signed integer types instead of unsigned counterparts (int32 and int64 types instead of uint32 and uint64). For most use cases we believe they provide sufficient range of values. If you run into problems, please open an issue on GitHub.

# Usage Samples
## RPC Read API
![Read API Blueprints](/imgs/read_api_nodes.png "Read API Blueprints")
### Get Object
Blueprint:

![GetObject Blueprint](/imgs/get_object.png "GetObject Blueprint Node")

C++:
```cpp
	auto Client = RpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		UE_LOG(LogTemp, Log, TEXT("Response received."));
	});
	Client.GetObject(ObjectId, RpcSuccessDelegate);
```
## RPC Historical Event Read API
![Historical Event Read API Blueprints](/imgs/event_read_api_nodes.png "Historical Event Read API Blueprints")

## Transaction API
![Transaction API Blueprints](/imgs/transaction_api_nodes.png "Transaction API Blueprints")

Call Mint Devnet NFT move contract:

![Mint Devnet NFT Blueprints](/imgs/mint_devnet_nft.png "Mint Devnet NFT Blueprints")

Sign And Execute Transactions:

![Sign And Execute Transactions](/imgs/sign_execute_transaction.png "Sign And Execute Transactions")

## Crypto Helper API
![Crypto Helper API Blueprints](/imgs/crypto_helpers_nodes.png "Crypto Helper API Blueprints")

# Copy paste ready Blueprint Nodes
[Copy paste ready Blueprint Nodes](https://blueprintue.com/blueprint/wcm2f6op/)

# Dependencies
The SDK Plugin currently depends on the [VaRest](https://www.unrealengine.com/marketplace/en-US/product/varest-plugin) plugin available from the marketplace.
All the other Dependencies can be found in the Plugins folder.

# Roadmap
- More platform support (iOS, Android, Mac)
- Streaming RPC client, Event subscription
- More RPC APIs and type bindings
- WalletConnect support
- More samples
- Origin-Byte NFT ecosystem access from Unreal Engine
- Higher level APIs, easy-to-use Blueprint nodes
