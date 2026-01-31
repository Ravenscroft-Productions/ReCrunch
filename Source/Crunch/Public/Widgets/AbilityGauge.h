// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "AbilityGauge.generated.h"

class UGameplayAbility;
class UTextBlock;
class UImage;

USTRUCT(BlueprintType)
struct FAbilityWidgetData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> AbilityClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName AbilityName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Icon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
};

/**
 * 
 */
UCLASS()
class CRUNCH_API UAbilityGauge : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	void ConfigureWithWidgetData(const FAbilityWidgetData* WidgetData);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Cooldown")
	float CooldownUpdateInterval = 0.1f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	FName IconMaterialParamName = "Icon";
	
	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	FName CooldownPercentParamName = "Percent";
	
	UPROPERTY(Meta = (BindWidget))
	UImage* Icon;
	
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* CooldownCounterText;
	
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* CooldownDurationText;
	
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* CostText;
	
	UPROPERTY()
	UGameplayAbility* AbilityCDO;
	
	void AbilityCommitted(UGameplayAbility* Ability);
	void StartCooldown(float CooldownTimeRemaining, float CooldownDuration);
	void CooldownFinished();
	void UpdateCooldown();
	
	float CachedCooldownDuration;
	float CachedCooldownTimeRemaining;
	FTimerHandle CooldownTimerHandle;
	FTimerHandle CooldownTimerUpdateHandle;
	FNumberFormattingOptions WholeNumberFormattingOptions;
	FNumberFormattingOptions TwoDigitNumberFormattingOptions;
};
