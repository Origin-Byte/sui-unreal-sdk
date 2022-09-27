# sui-unreal-sdk

Connecting Unreal game developers to Sui blockchain and Origin Byte's NFT ecosystem.

# Features
- For Rpc clients’ direct interaction with the Sui JSON-RPC https://docs.sui.io/sui-jsonrpc
- Tested on Windows desktop
- Works with Unreal Engine 5

# Getting Started
## Quickstart: download this repository and open with Unreal Engine 5
Check the Sample Level and the Blueprint Nodes in the Level Blueprint.

# Usage Samples
## RPC Read API
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




[Copy paste Blueprint Nodes](https://blueprintue.com/blueprint/qy5ko103/)
