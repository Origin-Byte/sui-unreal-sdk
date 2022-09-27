# sui-unreal-sdk

Connecting Unreal game developers to Sui and Origin Byte's NFT ecosystem.

# Features
- For Rpc clients’ direct interaction with the Sui JSON-RPC https://docs.sui.io/sui-jsonrpc
- Tested on Windows desktop
- Works with Unreal Engine 5

# Getting Started
## Quickstart: download this repository and open with Unreal Engine 5
Check the Sample Level and the Blueprint Nodes in the Level Blueprint.

# Usage Samples
## RPC Read API
![GetObject Blueprint](/imgs/getobject.png "GetObject Blueprint Node")
[Blueprint](https://blueprintue.com/blueprint/-0k1huc_/)

```cpp
	auto Client = RpcClient(Endpoint);
	FRpcSuccessDelegate RpcSuccessDelegate;
	RpcSuccessDelegate.BindLambda([OnResult](const FJsonRpcValidResponse& RpcResponse) {
		UE_LOG(LogTemp, Log, TEXT("Response received."));
	});
	Client.GetObject(ObjectId, RpcSuccessDelegate);
```