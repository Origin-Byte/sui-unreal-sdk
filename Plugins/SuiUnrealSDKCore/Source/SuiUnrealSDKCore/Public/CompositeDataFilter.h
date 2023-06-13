#pragma once
#include "CompositeDataFilter.generated.h"

UCLASS(BlueprintType, Abstract)
class SUIUNREALSDKCORE_API UDataFilterComponent : public UObject
{
	GENERATED_BODY()

public:
	virtual TSharedPtr<FJsonValue> ToJson() const
	{
		check(0 && "ToJson() must be overridden in subclasses");
		return TSharedPtr<FJsonValue>();
	}
};

UCLASS(BlueprintType)
class SUIUNREALSDKCORE_API UCompositeFilter : public UDataFilterComponent
{
	GENERATED_BODY()

public:
	void AddFilter(UDataFilterComponent* Filter);

	virtual TSharedPtr<FJsonValue> ToJson() const override;

private:
	UPROPERTY()
	TArray<UDataFilterComponent*> Filters;
};

UCLASS(BlueprintType)
class SUIUNREALSDKCORE_API UPackageDataFilter : public UDataFilterComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Sui | Package Data Filter")
	FString Package;

	virtual TSharedPtr<FJsonValue> ToJson() const override;

	UFUNCTION(BlueprintCallable, Category = "Sui | Package Data Filter", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UPackageDataFilter* CreatePackageDataFilter(UObject* WorldContextObject, const FString& InPackage);
};

UCLASS(BlueprintType)
class SUIUNREALSDKCORE_API UMoveModuleDataFilter : public UDataFilterComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Sui | Move Module Data Filter")
	FString ModuleName;

	UPROPERTY(BlueprintReadWrite, Category = "Sui | Move Module Data Filter")
	FString Package;

	virtual TSharedPtr<FJsonValue> ToJson() const override;

	UFUNCTION(BlueprintCallable, Category = "Sui | Move Module Data Filter", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UMoveModuleDataFilter* CreateMoveModuleDataFilter(UObject* WorldContextObject, const FString& InModuleName, const FString& InPackage);
};

UCLASS(BlueprintType)
class SUIUNREALSDKCORE_API UStructTypeDataFilter : public UDataFilterComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Sui | Struct Type Data Filter")
	FString StructType;

	virtual TSharedPtr<FJsonValue> ToJson() const override;

	UFUNCTION(BlueprintCallable, Category = "Sui | Struct Type Data Filter", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UStructTypeDataFilter* CreateStructTypeDataFilter(UObject* WorldContextObject, const FString& InStructType);
};

UCLASS(BlueprintType)
class SUIUNREALSDKCORE_API UAddressDataFilter : public UDataFilterComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Sui | Address Data Filter")
	FString Address;

	virtual TSharedPtr<FJsonValue> ToJson() const override;

	UFUNCTION(BlueprintCallable, Category = "Sui | Address Data Filter", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UAddressDataFilter* CreateAddressDataFilter(UObject* WorldContextObject, const FString& InAddress);
};

// Composite filters
UCLASS(BlueprintType)
class SUIUNREALSDKCORE_API UMatchAllDataFilter : public UDataFilterComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Sui | Match All Data Filter")
	TArray<UDataFilterComponent*> Filters;

	virtual TSharedPtr<FJsonValue> ToJson() const override;

	UFUNCTION(BlueprintCallable, Category = "Sui | Match All Data Filter", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UMatchAllDataFilter* CreateMatchAllDataFilter(UObject* WorldContextObject, const TArray<UDataFilterComponent*>& InFilters);
};

UCLASS(BlueprintType)
class SUIUNREALSDKCORE_API UMatchAnyDataFilter : public UDataFilterComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Sui | Match Any Data Filter")
	TArray<UDataFilterComponent*> Filters;

	virtual TSharedPtr<FJsonValue> ToJson() const override;

	UFUNCTION(BlueprintCallable, Category = "Sui | Match Any Data Filter", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UMatchAnyDataFilter* CreateMatchAnyDataFilter(UObject* WorldContextObject, const TArray<UDataFilterComponent*>& InFilters);
};

UCLASS(BlueprintType)
class SUIUNREALSDKCORE_API UMatchNoneDataFilter : public UDataFilterComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Sui | Match None Data Filter")
	TArray<UDataFilterComponent*> Filters;

	virtual TSharedPtr<FJsonValue> ToJson() const override;

	UFUNCTION(BlueprintCallable, Category = "Sui | Match None Data Filter", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UMatchNoneDataFilter* CreateMatchNoneDataFilter(UObject* WorldContextObject, const TArray<UDataFilterComponent*>& InFilters);
};