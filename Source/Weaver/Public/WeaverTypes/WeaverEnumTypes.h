#pragma once

UENUM()
enum class EWeaverConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EWeaverValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class EWeaverSuccessType : uint8
{
	Successful,
	Failed
};

UENUM()
enum class EWeaverCountdownActionInput : uint8
{
	Start,
	Cancel
};

UENUM()
enum class EWeaverCountdownActionOutput : uint8
{
	Updated,
	Completed,
	Cancelled
};

UENUM(BlueprintType)
enum class EWeaverInputMode : uint8
{
	GameOnly,
	UIOnly
};