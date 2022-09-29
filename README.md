# sui-unreal-sdk

Connecting Unreal game developers to Sui blockchain and Origin Byte's NFT ecosystem.

# Features
- For Rpc clients’ direct interaction with the Sui JSON-RPC https://docs.sui.io/sui-jsonrpc
- Tested on Windows desktop with Sui version 0.10.0
- Works with Unreal Engine 5

# Getting Started
## Quickstart: download this repository and open with Unreal Engine 5
Check the Sample Level and the Blueprint Nodes in the Level Blueprint.

# Usage Samples
## RPC Read API
![Read API Blueprints](/imgs/read_api_nodes.png "Read API Blueprints")
### Get Object
![GetObject Blueprint](/imgs/get_object.png "GetObject Blueprint Node")

```cpp
	auto Client = RpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		UE_LOG(LogTemp, Log, TEXT("Response received."));
	});
	Client.GetObject(ObjectId, RpcSuccessDelegate);
```

### Get Objects Owned By Address
![GetObjectsOwnedByAddress Blueprint](/imgs/get_objects_owned_by_address.png "GetObjectsOwnedByAddress Blueprint Node")

### Get Objects Owned By Object
![GetObjectsOwnedByObject Blueprint](/imgs/get_objects_owned_by_object.png "GetObjectsOwnedByObject Blueprint Node")

## Transaction API
![Transaction API Blueprints](/imgs/transaction_api_nodes.png "Transaction API Blueprints")

## Crypto Helpers API
![Crypto Helpers API Blueprints](/imgs/crypto_helpers_nodes.png "Crypto Helpers API Blueprints")


[Copy paste Blueprint Nodes](https://blueprintue.com/blueprint/k30t8ebp/)

# Dependencies
The SDK currently depends on the [VaRest](https://www.unrealengine.com/marketplace/en-US/product/varest-plugin) plugin.

# Roadmap
- More platform support (iOS, Android, Mac)
- Streaming RPC client, Event subscription
- More samples
- Origin-Byte NFT ecosystem access from Unity
- More type bindings
- Higher level APIs, easy-to-use Blueprint nodes
