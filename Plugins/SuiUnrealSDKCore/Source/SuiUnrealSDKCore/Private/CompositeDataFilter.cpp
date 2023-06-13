#include "CompositeDataFilter.h"

void UCompositeFilter::AddFilter(UDataFilterComponent* Filter)
{
	Filters.Add(Filter);
}

TSharedPtr<FJsonValue> UCompositeFilter::ToJson() const
{
	TArray<TSharedPtr<FJsonValue>> JsonArray;
	for (const UDataFilterComponent* Filter : Filters)
	{
		JsonArray.Add(Filter->ToJson());
	}
	return MakeShareable(new FJsonValueArray(JsonArray));
}

TSharedPtr<FJsonValue> UPackageDataFilter::ToJson() const
{
	const TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject);
	JsonObj->SetStringField("Package", Package);
	return MakeShareable(new FJsonValueObject(JsonObj));
}

UPackageDataFilter* UPackageDataFilter::MakePackageDataFilter(UObject* WorldContextObject, const FString& InPackage)
{
	const auto NewFilter = NewObject<UPackageDataFilter>(WorldContextObject);
	NewFilter->Package = InPackage;
	return NewFilter;
}

TSharedPtr<FJsonValue> UMoveModuleDataFilter::ToJson() const
{
	const TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject);
	JsonObj->SetStringField("module", ModuleName);
	JsonObj->SetStringField("package", Package);
	return MakeShareable(new FJsonValueObject(JsonObj));
}

UMoveModuleDataFilter* UMoveModuleDataFilter::MakeMoveModuleDataFilter(UObject* WorldContextObject,
	const FString& InModuleName, const FString& InPackage)
{
	const auto NewFilter = NewObject<UMoveModuleDataFilter>(WorldContextObject);
	NewFilter->Package = InPackage;
	NewFilter->ModuleName = InModuleName;
	return NewFilter;
}

TSharedPtr<FJsonValue> UStructTypeDataFilter::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject);
	JsonObj->SetStringField("StructType", StructType);
	return MakeShareable(new FJsonValueObject(JsonObj));
}

UStructTypeDataFilter* UStructTypeDataFilter::MakeStructTypeDataFilter(UObject* WorldContextObject,
	const FString& InStructType)
{
	const auto NewFilter = NewObject<UStructTypeDataFilter>(WorldContextObject);
	NewFilter->StructType = InStructType;
	return NewFilter;
}

TSharedPtr<FJsonValue> UAddressDataFilter::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject);
	JsonObj->SetStringField("AddressOwner", Address);
	return MakeShareable(new FJsonValueObject(JsonObj));
}

UAddressDataFilter* UAddressDataFilter::MakeAddressDataFilter(UObject* WorldContextObject, const FString& InAddress)
{
	const auto NewFilter = NewObject<UAddressDataFilter>(WorldContextObject);
	NewFilter->Address = InAddress;
	return NewFilter;
}

TSharedPtr<FJsonValue> UMatchAllDataFilter::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject);
	TArray<TSharedPtr<FJsonValue>> JsonValues;
	for (UDataFilterComponent* Filter : Filters)
	{
		JsonValues.Add(Filter->ToJson());
	}
	JsonObj->SetArrayField("MatchAll", JsonValues);
	return MakeShareable(new FJsonValueObject(JsonObj));
}

UMatchAllDataFilter* UMatchAllDataFilter::MakeMatchAllDataFilter(UObject* WorldContextObject,
                                                               const TArray<UDataFilterComponent*>& InFilters)
{
	UMatchAllDataFilter* NewFilter = NewObject<UMatchAllDataFilter>(WorldContextObject);
	NewFilter->Filters = InFilters;
	return NewFilter;
}

TSharedPtr<FJsonValue> UMatchAnyDataFilter::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject);
	TArray<TSharedPtr<FJsonValue>> JsonValues;
	for (UDataFilterComponent* Filter : Filters)
	{
		JsonValues.Add(Filter->ToJson());
	}
	JsonObj->SetArrayField("MatchAny", JsonValues);
	return MakeShareable(new FJsonValueObject(JsonObj));
}

UMatchAnyDataFilter* UMatchAnyDataFilter::MakeMatchAnyDataFilter(UObject* WorldContextObject,
	const TArray<UDataFilterComponent*>& InFilters)
{
	UMatchAnyDataFilter* NewFilter = NewObject<UMatchAnyDataFilter>(WorldContextObject);
	NewFilter->Filters = InFilters;
	return NewFilter;
}

TSharedPtr<FJsonValue> UMatchNoneDataFilter::ToJson() const
{
	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject);
	TArray<TSharedPtr<FJsonValue>> JsonValues;
	for (UDataFilterComponent* Filter : Filters)
	{
		JsonValues.Add(Filter->ToJson());
	}
	JsonObj->SetArrayField("MatchNone", JsonValues);
	return MakeShareable(new FJsonValueObject(JsonObj));
}

UMatchNoneDataFilter* UMatchNoneDataFilter::MakeMatchNoneDataFilter(UObject* WorldContextObject,
	const TArray<UDataFilterComponent*>& InFilters)
{
	UMatchNoneDataFilter* NewFilter = NewObject<UMatchNoneDataFilter>(WorldContextObject);
	NewFilter->Filters = InFilters;
	return NewFilter;
}
