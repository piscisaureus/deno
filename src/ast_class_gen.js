class Node {}
exports.Node = Node;

class Attr extends Node {
  get kind() {
    return "Attr";
  }
}
exports.Attr = Attr;

class AddressSpaceAttr extends Attr {
  get kind() {
    return "AddressSpaceAttr";
  }
}
exports.AddressSpaceAttr = AddressSpaceAttr;
class NoDerefAttr extends Attr {
  get kind() {
    return "NoDerefAttr";
  }
}
exports.NoDerefAttr = NoDerefAttr;
class ObjCGCAttr extends Attr {
  get kind() {
    return "ObjCGCAttr";
  }
}
exports.ObjCGCAttr = ObjCGCAttr;
class ObjCInertUnsafeUnretainedAttr extends Attr {
  get kind() {
    return "ObjCInertUnsafeUnretainedAttr";
  }
}
exports.ObjCInertUnsafeUnretainedAttr = ObjCInertUnsafeUnretainedAttr;
class ObjCKindOfAttr extends Attr {
  get kind() {
    return "ObjCKindOfAttr";
  }
}
exports.ObjCKindOfAttr = ObjCKindOfAttr;
class OpenCLConstantAddressSpaceAttr extends Attr {
  get kind() {
    return "OpenCLConstantAddressSpaceAttr";
  }
}
exports.OpenCLConstantAddressSpaceAttr = OpenCLConstantAddressSpaceAttr;
class OpenCLGenericAddressSpaceAttr extends Attr {
  get kind() {
    return "OpenCLGenericAddressSpaceAttr";
  }
}
exports.OpenCLGenericAddressSpaceAttr = OpenCLGenericAddressSpaceAttr;
class OpenCLGlobalAddressSpaceAttr extends Attr {
  get kind() {
    return "OpenCLGlobalAddressSpaceAttr";
  }
}
exports.OpenCLGlobalAddressSpaceAttr = OpenCLGlobalAddressSpaceAttr;
class OpenCLLocalAddressSpaceAttr extends Attr {
  get kind() {
    return "OpenCLLocalAddressSpaceAttr";
  }
}
exports.OpenCLLocalAddressSpaceAttr = OpenCLLocalAddressSpaceAttr;
class OpenCLPrivateAddressSpaceAttr extends Attr {
  get kind() {
    return "OpenCLPrivateAddressSpaceAttr";
  }
}
exports.OpenCLPrivateAddressSpaceAttr = OpenCLPrivateAddressSpaceAttr;
class Ptr32Attr extends Attr {
  get kind() {
    return "Ptr32Attr";
  }
}
exports.Ptr32Attr = Ptr32Attr;
class Ptr64Attr extends Attr {
  get kind() {
    return "Ptr64Attr";
  }
}
exports.Ptr64Attr = Ptr64Attr;
class SPtrAttr extends Attr {
  get kind() {
    return "SPtrAttr";
  }
}
exports.SPtrAttr = SPtrAttr;
class TypeNonNullAttr extends Attr {
  get kind() {
    return "TypeNonNullAttr";
  }
}
exports.TypeNonNullAttr = TypeNonNullAttr;
class TypeNullUnspecifiedAttr extends Attr {
  get kind() {
    return "TypeNullUnspecifiedAttr";
  }
}
exports.TypeNullUnspecifiedAttr = TypeNullUnspecifiedAttr;
class TypeNullableAttr extends Attr {
  get kind() {
    return "TypeNullableAttr";
  }
}
exports.TypeNullableAttr = TypeNullableAttr;
class UPtrAttr extends Attr {
  get kind() {
    return "UPtrAttr";
  }
}
exports.UPtrAttr = UPtrAttr;
class FallThroughAttr extends Attr {
  get kind() {
    return "FallThroughAttr";
  }
}
exports.FallThroughAttr = FallThroughAttr;
class SuppressAttr extends Attr {
  get kind() {
    return "SuppressAttr";
  }
}
exports.SuppressAttr = SuppressAttr;
class AArch64VectorPcsAttr extends Attr {
  get kind() {
    return "AArch64VectorPcsAttr";
  }
}
exports.AArch64VectorPcsAttr = AArch64VectorPcsAttr;
class AnyX86NoCfCheckAttr extends Attr {
  get kind() {
    return "AnyX86NoCfCheckAttr";
  }
}
exports.AnyX86NoCfCheckAttr = AnyX86NoCfCheckAttr;
class CDeclAttr extends Attr {
  get kind() {
    return "CDeclAttr";
  }
}
exports.CDeclAttr = CDeclAttr;
class FastCallAttr extends Attr {
  get kind() {
    return "FastCallAttr";
  }
}
exports.FastCallAttr = FastCallAttr;
class IntelOclBiccAttr extends Attr {
  get kind() {
    return "IntelOclBiccAttr";
  }
}
exports.IntelOclBiccAttr = IntelOclBiccAttr;
class LifetimeBoundAttr extends Attr {
  get kind() {
    return "LifetimeBoundAttr";
  }
}
exports.LifetimeBoundAttr = LifetimeBoundAttr;
class MSABIAttr extends Attr {
  get kind() {
    return "MSABIAttr";
  }
}
exports.MSABIAttr = MSABIAttr;
class NSReturnsRetainedAttr extends Attr {
  get kind() {
    return "NSReturnsRetainedAttr";
  }
}
exports.NSReturnsRetainedAttr = NSReturnsRetainedAttr;
class ObjCOwnershipAttr extends Attr {
  get kind() {
    return "ObjCOwnershipAttr";
  }
}
exports.ObjCOwnershipAttr = ObjCOwnershipAttr;
class PascalAttr extends Attr {
  get kind() {
    return "PascalAttr";
  }
}
exports.PascalAttr = PascalAttr;
class PcsAttr extends Attr {
  get kind() {
    return "PcsAttr";
  }
}
exports.PcsAttr = PcsAttr;
class PreserveAllAttr extends Attr {
  get kind() {
    return "PreserveAllAttr";
  }
}
exports.PreserveAllAttr = PreserveAllAttr;
class PreserveMostAttr extends Attr {
  get kind() {
    return "PreserveMostAttr";
  }
}
exports.PreserveMostAttr = PreserveMostAttr;
class RegCallAttr extends Attr {
  get kind() {
    return "RegCallAttr";
  }
}
exports.RegCallAttr = RegCallAttr;
class StdCallAttr extends Attr {
  get kind() {
    return "StdCallAttr";
  }
}
exports.StdCallAttr = StdCallAttr;
class SwiftCallAttr extends Attr {
  get kind() {
    return "SwiftCallAttr";
  }
}
exports.SwiftCallAttr = SwiftCallAttr;
class SysVABIAttr extends Attr {
  get kind() {
    return "SysVABIAttr";
  }
}
exports.SysVABIAttr = SysVABIAttr;
class ThisCallAttr extends Attr {
  get kind() {
    return "ThisCallAttr";
  }
}
exports.ThisCallAttr = ThisCallAttr;
class VectorCallAttr extends Attr {
  get kind() {
    return "VectorCallAttr";
  }
}
exports.VectorCallAttr = VectorCallAttr;
class SwiftContextAttr extends Attr {
  get kind() {
    return "SwiftContextAttr";
  }
}
exports.SwiftContextAttr = SwiftContextAttr;
class SwiftErrorResultAttr extends Attr {
  get kind() {
    return "SwiftErrorResultAttr";
  }
}
exports.SwiftErrorResultAttr = SwiftErrorResultAttr;
class SwiftIndirectResultAttr extends Attr {
  get kind() {
    return "SwiftIndirectResultAttr";
  }
}
exports.SwiftIndirectResultAttr = SwiftIndirectResultAttr;
class AnnotateAttr extends Attr {
  get kind() {
    return "AnnotateAttr";
  }
}
exports.AnnotateAttr = AnnotateAttr;
class CFConsumedAttr extends Attr {
  get kind() {
    return "CFConsumedAttr";
  }
}
exports.CFConsumedAttr = CFConsumedAttr;
class CarriesDependencyAttr extends Attr {
  get kind() {
    return "CarriesDependencyAttr";
  }
}
exports.CarriesDependencyAttr = CarriesDependencyAttr;
class NSConsumedAttr extends Attr {
  get kind() {
    return "NSConsumedAttr";
  }
}
exports.NSConsumedAttr = NSConsumedAttr;
class NonNullAttr extends Attr {
  get kind() {
    return "NonNullAttr";
  }
}
exports.NonNullAttr = NonNullAttr;
class OSConsumedAttr extends Attr {
  get kind() {
    return "OSConsumedAttr";
  }
}
exports.OSConsumedAttr = OSConsumedAttr;
class PassObjectSizeAttr extends Attr {
  get kind() {
    return "PassObjectSizeAttr";
  }
}
exports.PassObjectSizeAttr = PassObjectSizeAttr;
class AMDGPUFlatWorkGroupSizeAttr extends Attr {
  get kind() {
    return "AMDGPUFlatWorkGroupSizeAttr";
  }
}
exports.AMDGPUFlatWorkGroupSizeAttr = AMDGPUFlatWorkGroupSizeAttr;
class AMDGPUNumSGPRAttr extends Attr {
  get kind() {
    return "AMDGPUNumSGPRAttr";
  }
}
exports.AMDGPUNumSGPRAttr = AMDGPUNumSGPRAttr;
class AMDGPUNumVGPRAttr extends Attr {
  get kind() {
    return "AMDGPUNumVGPRAttr";
  }
}
exports.AMDGPUNumVGPRAttr = AMDGPUNumVGPRAttr;
class AMDGPUWavesPerEUAttr extends Attr {
  get kind() {
    return "AMDGPUWavesPerEUAttr";
  }
}
exports.AMDGPUWavesPerEUAttr = AMDGPUWavesPerEUAttr;
class ARMInterruptAttr extends Attr {
  get kind() {
    return "ARMInterruptAttr";
  }
}
exports.ARMInterruptAttr = ARMInterruptAttr;
class AVRInterruptAttr extends Attr {
  get kind() {
    return "AVRInterruptAttr";
  }
}
exports.AVRInterruptAttr = AVRInterruptAttr;
class AVRSignalAttr extends Attr {
  get kind() {
    return "AVRSignalAttr";
  }
}
exports.AVRSignalAttr = AVRSignalAttr;
class AcquireCapabilityAttr extends Attr {
  get kind() {
    return "AcquireCapabilityAttr";
  }
}
exports.AcquireCapabilityAttr = AcquireCapabilityAttr;
class AcquiredAfterAttr extends Attr {
  get kind() {
    return "AcquiredAfterAttr";
  }
}
exports.AcquiredAfterAttr = AcquiredAfterAttr;
class AcquiredBeforeAttr extends Attr {
  get kind() {
    return "AcquiredBeforeAttr";
  }
}
exports.AcquiredBeforeAttr = AcquiredBeforeAttr;
class AlignMac68kAttr extends Attr {
  get kind() {
    return "AlignMac68kAttr";
  }
}
exports.AlignMac68kAttr = AlignMac68kAttr;
class AlignedAttr extends Attr {
  get kind() {
    return "AlignedAttr";
  }
}
exports.AlignedAttr = AlignedAttr;
class AllocAlignAttr extends Attr {
  get kind() {
    return "AllocAlignAttr";
  }
}
exports.AllocAlignAttr = AllocAlignAttr;
class AllocSizeAttr extends Attr {
  get kind() {
    return "AllocSizeAttr";
  }
}
exports.AllocSizeAttr = AllocSizeAttr;
class AlwaysDestroyAttr extends Attr {
  get kind() {
    return "AlwaysDestroyAttr";
  }
}
exports.AlwaysDestroyAttr = AlwaysDestroyAttr;
class AlwaysInlineAttr extends Attr {
  get kind() {
    return "AlwaysInlineAttr";
  }
}
exports.AlwaysInlineAttr = AlwaysInlineAttr;
class AnalyzerNoReturnAttr extends Attr {
  get kind() {
    return "AnalyzerNoReturnAttr";
  }
}
exports.AnalyzerNoReturnAttr = AnalyzerNoReturnAttr;
class AnyX86InterruptAttr extends Attr {
  get kind() {
    return "AnyX86InterruptAttr";
  }
}
exports.AnyX86InterruptAttr = AnyX86InterruptAttr;
class AnyX86NoCallerSavedRegistersAttr extends Attr {
  get kind() {
    return "AnyX86NoCallerSavedRegistersAttr";
  }
}
exports.AnyX86NoCallerSavedRegistersAttr = AnyX86NoCallerSavedRegistersAttr;
class ArcWeakrefUnavailableAttr extends Attr {
  get kind() {
    return "ArcWeakrefUnavailableAttr";
  }
}
exports.ArcWeakrefUnavailableAttr = ArcWeakrefUnavailableAttr;
class ArgumentWithTypeTagAttr extends Attr {
  get kind() {
    return "ArgumentWithTypeTagAttr";
  }
}
exports.ArgumentWithTypeTagAttr = ArgumentWithTypeTagAttr;
class ArtificialAttr extends Attr {
  get kind() {
    return "ArtificialAttr";
  }
}
exports.ArtificialAttr = ArtificialAttr;
class AsmLabelAttr extends Attr {
  get kind() {
    return "AsmLabelAttr";
  }
}
exports.AsmLabelAttr = AsmLabelAttr;
class AssertCapabilityAttr extends Attr {
  get kind() {
    return "AssertCapabilityAttr";
  }
}
exports.AssertCapabilityAttr = AssertCapabilityAttr;
class AssertExclusiveLockAttr extends Attr {
  get kind() {
    return "AssertExclusiveLockAttr";
  }
}
exports.AssertExclusiveLockAttr = AssertExclusiveLockAttr;
class AssertSharedLockAttr extends Attr {
  get kind() {
    return "AssertSharedLockAttr";
  }
}
exports.AssertSharedLockAttr = AssertSharedLockAttr;
class AssumeAlignedAttr extends Attr {
  get kind() {
    return "AssumeAlignedAttr";
  }
}
exports.AssumeAlignedAttr = AssumeAlignedAttr;
class AvailabilityAttr extends Attr {
  get kind() {
    return "AvailabilityAttr";
  }
}
exports.AvailabilityAttr = AvailabilityAttr;
class BlocksAttr extends Attr {
  get kind() {
    return "BlocksAttr";
  }
}
exports.BlocksAttr = BlocksAttr;
class C11NoReturnAttr extends Attr {
  get kind() {
    return "C11NoReturnAttr";
  }
}
exports.C11NoReturnAttr = C11NoReturnAttr;
class CFAuditedTransferAttr extends Attr {
  get kind() {
    return "CFAuditedTransferAttr";
  }
}
exports.CFAuditedTransferAttr = CFAuditedTransferAttr;
class CFICanonicalJumpTableAttr extends Attr {
  get kind() {
    return "CFICanonicalJumpTableAttr";
  }
}
exports.CFICanonicalJumpTableAttr = CFICanonicalJumpTableAttr;
class CFReturnsNotRetainedAttr extends Attr {
  get kind() {
    return "CFReturnsNotRetainedAttr";
  }
}
exports.CFReturnsNotRetainedAttr = CFReturnsNotRetainedAttr;
class CFReturnsRetainedAttr extends Attr {
  get kind() {
    return "CFReturnsRetainedAttr";
  }
}
exports.CFReturnsRetainedAttr = CFReturnsRetainedAttr;
class CFUnknownTransferAttr extends Attr {
  get kind() {
    return "CFUnknownTransferAttr";
  }
}
exports.CFUnknownTransferAttr = CFUnknownTransferAttr;
class CPUDispatchAttr extends Attr {
  get kind() {
    return "CPUDispatchAttr";
  }
}
exports.CPUDispatchAttr = CPUDispatchAttr;
class CPUSpecificAttr extends Attr {
  get kind() {
    return "CPUSpecificAttr";
  }
}
exports.CPUSpecificAttr = CPUSpecificAttr;
class CUDAConstantAttr extends Attr {
  get kind() {
    return "CUDAConstantAttr";
  }
}
exports.CUDAConstantAttr = CUDAConstantAttr;
class CUDADeviceAttr extends Attr {
  get kind() {
    return "CUDADeviceAttr";
  }
}
exports.CUDADeviceAttr = CUDADeviceAttr;
class CUDAGlobalAttr extends Attr {
  get kind() {
    return "CUDAGlobalAttr";
  }
}
exports.CUDAGlobalAttr = CUDAGlobalAttr;
class CUDAHostAttr extends Attr {
  get kind() {
    return "CUDAHostAttr";
  }
}
exports.CUDAHostAttr = CUDAHostAttr;
class CUDAInvalidTargetAttr extends Attr {
  get kind() {
    return "CUDAInvalidTargetAttr";
  }
}
exports.CUDAInvalidTargetAttr = CUDAInvalidTargetAttr;
class CUDALaunchBoundsAttr extends Attr {
  get kind() {
    return "CUDALaunchBoundsAttr";
  }
}
exports.CUDALaunchBoundsAttr = CUDALaunchBoundsAttr;
class CUDASharedAttr extends Attr {
  get kind() {
    return "CUDASharedAttr";
  }
}
exports.CUDASharedAttr = CUDASharedAttr;
class CXX11NoReturnAttr extends Attr {
  get kind() {
    return "CXX11NoReturnAttr";
  }
}
exports.CXX11NoReturnAttr = CXX11NoReturnAttr;
class CallableWhenAttr extends Attr {
  get kind() {
    return "CallableWhenAttr";
  }
}
exports.CallableWhenAttr = CallableWhenAttr;
class CallbackAttr extends Attr {
  get kind() {
    return "CallbackAttr";
  }
}
exports.CallbackAttr = CallbackAttr;
class CapabilityAttr extends Attr {
  get kind() {
    return "CapabilityAttr";
  }
}
exports.CapabilityAttr = CapabilityAttr;
class CapturedRecordAttr extends Attr {
  get kind() {
    return "CapturedRecordAttr";
  }
}
exports.CapturedRecordAttr = CapturedRecordAttr;
class CleanupAttr extends Attr {
  get kind() {
    return "CleanupAttr";
  }
}
exports.CleanupAttr = CleanupAttr;
class CodeSegAttr extends Attr {
  get kind() {
    return "CodeSegAttr";
  }
}
exports.CodeSegAttr = CodeSegAttr;
class ColdAttr extends Attr {
  get kind() {
    return "ColdAttr";
  }
}
exports.ColdAttr = ColdAttr;
class CommonAttr extends Attr {
  get kind() {
    return "CommonAttr";
  }
}
exports.CommonAttr = CommonAttr;
class ConstAttr extends Attr {
  get kind() {
    return "ConstAttr";
  }
}
exports.ConstAttr = ConstAttr;
class ConstructorAttr extends Attr {
  get kind() {
    return "ConstructorAttr";
  }
}
exports.ConstructorAttr = ConstructorAttr;
class ConsumableAttr extends Attr {
  get kind() {
    return "ConsumableAttr";
  }
}
exports.ConsumableAttr = ConsumableAttr;
class ConsumableAutoCastAttr extends Attr {
  get kind() {
    return "ConsumableAutoCastAttr";
  }
}
exports.ConsumableAutoCastAttr = ConsumableAutoCastAttr;
class ConsumableSetOnReadAttr extends Attr {
  get kind() {
    return "ConsumableSetOnReadAttr";
  }
}
exports.ConsumableSetOnReadAttr = ConsumableSetOnReadAttr;
class ConvergentAttr extends Attr {
  get kind() {
    return "ConvergentAttr";
  }
}
exports.ConvergentAttr = ConvergentAttr;
class DLLExportAttr extends Attr {
  get kind() {
    return "DLLExportAttr";
  }
}
exports.DLLExportAttr = DLLExportAttr;
class DLLExportStaticLocalAttr extends Attr {
  get kind() {
    return "DLLExportStaticLocalAttr";
  }
}
exports.DLLExportStaticLocalAttr = DLLExportStaticLocalAttr;
class DLLImportAttr extends Attr {
  get kind() {
    return "DLLImportAttr";
  }
}
exports.DLLImportAttr = DLLImportAttr;
class DLLImportStaticLocalAttr extends Attr {
  get kind() {
    return "DLLImportStaticLocalAttr";
  }
}
exports.DLLImportStaticLocalAttr = DLLImportStaticLocalAttr;
class DeprecatedAttr extends Attr {
  get kind() {
    return "DeprecatedAttr";
  }
}
exports.DeprecatedAttr = DeprecatedAttr;
class DestructorAttr extends Attr {
  get kind() {
    return "DestructorAttr";
  }
}
exports.DestructorAttr = DestructorAttr;
class DiagnoseIfAttr extends Attr {
  get kind() {
    return "DiagnoseIfAttr";
  }
}
exports.DiagnoseIfAttr = DiagnoseIfAttr;
class DisableTailCallsAttr extends Attr {
  get kind() {
    return "DisableTailCallsAttr";
  }
}
exports.DisableTailCallsAttr = DisableTailCallsAttr;
class EmptyBasesAttr extends Attr {
  get kind() {
    return "EmptyBasesAttr";
  }
}
exports.EmptyBasesAttr = EmptyBasesAttr;
class EnableIfAttr extends Attr {
  get kind() {
    return "EnableIfAttr";
  }
}
exports.EnableIfAttr = EnableIfAttr;
class EnumExtensibilityAttr extends Attr {
  get kind() {
    return "EnumExtensibilityAttr";
  }
}
exports.EnumExtensibilityAttr = EnumExtensibilityAttr;
class ExcludeFromExplicitInstantiationAttr extends Attr {
  get kind() {
    return "ExcludeFromExplicitInstantiationAttr";
  }
}
exports.ExcludeFromExplicitInstantiationAttr = ExcludeFromExplicitInstantiationAttr;
class ExclusiveTrylockFunctionAttr extends Attr {
  get kind() {
    return "ExclusiveTrylockFunctionAttr";
  }
}
exports.ExclusiveTrylockFunctionAttr = ExclusiveTrylockFunctionAttr;
class ExternalSourceSymbolAttr extends Attr {
  get kind() {
    return "ExternalSourceSymbolAttr";
  }
}
exports.ExternalSourceSymbolAttr = ExternalSourceSymbolAttr;
class FinalAttr extends Attr {
  get kind() {
    return "FinalAttr";
  }
}
exports.FinalAttr = FinalAttr;
class FlagEnumAttr extends Attr {
  get kind() {
    return "FlagEnumAttr";
  }
}
exports.FlagEnumAttr = FlagEnumAttr;
class FlattenAttr extends Attr {
  get kind() {
    return "FlattenAttr";
  }
}
exports.FlattenAttr = FlattenAttr;
class FormatAttr extends Attr {
  get kind() {
    return "FormatAttr";
  }
}
exports.FormatAttr = FormatAttr;
class FormatArgAttr extends Attr {
  get kind() {
    return "FormatArgAttr";
  }
}
exports.FormatArgAttr = FormatArgAttr;
class GNUInlineAttr extends Attr {
  get kind() {
    return "GNUInlineAttr";
  }
}
exports.GNUInlineAttr = GNUInlineAttr;
class GuardedByAttr extends Attr {
  get kind() {
    return "GuardedByAttr";
  }
}
exports.GuardedByAttr = GuardedByAttr;
class GuardedVarAttr extends Attr {
  get kind() {
    return "GuardedVarAttr";
  }
}
exports.GuardedVarAttr = GuardedVarAttr;
class HIPPinnedShadowAttr extends Attr {
  get kind() {
    return "HIPPinnedShadowAttr";
  }
}
exports.HIPPinnedShadowAttr = HIPPinnedShadowAttr;
class HotAttr extends Attr {
  get kind() {
    return "HotAttr";
  }
}
exports.HotAttr = HotAttr;
class IBActionAttr extends Attr {
  get kind() {
    return "IBActionAttr";
  }
}
exports.IBActionAttr = IBActionAttr;
class IBOutletAttr extends Attr {
  get kind() {
    return "IBOutletAttr";
  }
}
exports.IBOutletAttr = IBOutletAttr;
class IBOutletCollectionAttr extends Attr {
  get kind() {
    return "IBOutletCollectionAttr";
  }
}
exports.IBOutletCollectionAttr = IBOutletCollectionAttr;
class InitPriorityAttr extends Attr {
  get kind() {
    return "InitPriorityAttr";
  }
}
exports.InitPriorityAttr = InitPriorityAttr;
class InternalLinkageAttr extends Attr {
  get kind() {
    return "InternalLinkageAttr";
  }
}
exports.InternalLinkageAttr = InternalLinkageAttr;
class LTOVisibilityPublicAttr extends Attr {
  get kind() {
    return "LTOVisibilityPublicAttr";
  }
}
exports.LTOVisibilityPublicAttr = LTOVisibilityPublicAttr;
class LayoutVersionAttr extends Attr {
  get kind() {
    return "LayoutVersionAttr";
  }
}
exports.LayoutVersionAttr = LayoutVersionAttr;
class LockReturnedAttr extends Attr {
  get kind() {
    return "LockReturnedAttr";
  }
}
exports.LockReturnedAttr = LockReturnedAttr;
class LocksExcludedAttr extends Attr {
  get kind() {
    return "LocksExcludedAttr";
  }
}
exports.LocksExcludedAttr = LocksExcludedAttr;
class MIGServerRoutineAttr extends Attr {
  get kind() {
    return "MIGServerRoutineAttr";
  }
}
exports.MIGServerRoutineAttr = MIGServerRoutineAttr;
class MSAllocatorAttr extends Attr {
  get kind() {
    return "MSAllocatorAttr";
  }
}
exports.MSAllocatorAttr = MSAllocatorAttr;
class MSInheritanceAttr extends Attr {
  get kind() {
    return "MSInheritanceAttr";
  }
}
exports.MSInheritanceAttr = MSInheritanceAttr;
class MSNoVTableAttr extends Attr {
  get kind() {
    return "MSNoVTableAttr";
  }
}
exports.MSNoVTableAttr = MSNoVTableAttr;
class MSP430InterruptAttr extends Attr {
  get kind() {
    return "MSP430InterruptAttr";
  }
}
exports.MSP430InterruptAttr = MSP430InterruptAttr;
class MSStructAttr extends Attr {
  get kind() {
    return "MSStructAttr";
  }
}
exports.MSStructAttr = MSStructAttr;
class MSVtorDispAttr extends Attr {
  get kind() {
    return "MSVtorDispAttr";
  }
}
exports.MSVtorDispAttr = MSVtorDispAttr;
class MaxFieldAlignmentAttr extends Attr {
  get kind() {
    return "MaxFieldAlignmentAttr";
  }
}
exports.MaxFieldAlignmentAttr = MaxFieldAlignmentAttr;
class MayAliasAttr extends Attr {
  get kind() {
    return "MayAliasAttr";
  }
}
exports.MayAliasAttr = MayAliasAttr;
class MicroMipsAttr extends Attr {
  get kind() {
    return "MicroMipsAttr";
  }
}
exports.MicroMipsAttr = MicroMipsAttr;
class MinSizeAttr extends Attr {
  get kind() {
    return "MinSizeAttr";
  }
}
exports.MinSizeAttr = MinSizeAttr;
class MinVectorWidthAttr extends Attr {
  get kind() {
    return "MinVectorWidthAttr";
  }
}
exports.MinVectorWidthAttr = MinVectorWidthAttr;
class Mips16Attr extends Attr {
  get kind() {
    return "Mips16Attr";
  }
}
exports.Mips16Attr = Mips16Attr;
class MipsInterruptAttr extends Attr {
  get kind() {
    return "MipsInterruptAttr";
  }
}
exports.MipsInterruptAttr = MipsInterruptAttr;
class MipsLongCallAttr extends Attr {
  get kind() {
    return "MipsLongCallAttr";
  }
}
exports.MipsLongCallAttr = MipsLongCallAttr;
class MipsShortCallAttr extends Attr {
  get kind() {
    return "MipsShortCallAttr";
  }
}
exports.MipsShortCallAttr = MipsShortCallAttr;
class NSConsumesSelfAttr extends Attr {
  get kind() {
    return "NSConsumesSelfAttr";
  }
}
exports.NSConsumesSelfAttr = NSConsumesSelfAttr;
class NSReturnsAutoreleasedAttr extends Attr {
  get kind() {
    return "NSReturnsAutoreleasedAttr";
  }
}
exports.NSReturnsAutoreleasedAttr = NSReturnsAutoreleasedAttr;
class NSReturnsNotRetainedAttr extends Attr {
  get kind() {
    return "NSReturnsNotRetainedAttr";
  }
}
exports.NSReturnsNotRetainedAttr = NSReturnsNotRetainedAttr;
class NakedAttr extends Attr {
  get kind() {
    return "NakedAttr";
  }
}
exports.NakedAttr = NakedAttr;
class NoAliasAttr extends Attr {
  get kind() {
    return "NoAliasAttr";
  }
}
exports.NoAliasAttr = NoAliasAttr;
class NoCommonAttr extends Attr {
  get kind() {
    return "NoCommonAttr";
  }
}
exports.NoCommonAttr = NoCommonAttr;
class NoDebugAttr extends Attr {
  get kind() {
    return "NoDebugAttr";
  }
}
exports.NoDebugAttr = NoDebugAttr;
class NoDestroyAttr extends Attr {
  get kind() {
    return "NoDestroyAttr";
  }
}
exports.NoDestroyAttr = NoDestroyAttr;
class NoDuplicateAttr extends Attr {
  get kind() {
    return "NoDuplicateAttr";
  }
}
exports.NoDuplicateAttr = NoDuplicateAttr;
class NoInlineAttr extends Attr {
  get kind() {
    return "NoInlineAttr";
  }
}
exports.NoInlineAttr = NoInlineAttr;
class NoInstrumentFunctionAttr extends Attr {
  get kind() {
    return "NoInstrumentFunctionAttr";
  }
}
exports.NoInstrumentFunctionAttr = NoInstrumentFunctionAttr;
class NoMicroMipsAttr extends Attr {
  get kind() {
    return "NoMicroMipsAttr";
  }
}
exports.NoMicroMipsAttr = NoMicroMipsAttr;
class NoMips16Attr extends Attr {
  get kind() {
    return "NoMips16Attr";
  }
}
exports.NoMips16Attr = NoMips16Attr;
class NoReturnAttr extends Attr {
  get kind() {
    return "NoReturnAttr";
  }
}
exports.NoReturnAttr = NoReturnAttr;
class NoSanitizeAttr extends Attr {
  get kind() {
    return "NoSanitizeAttr";
  }
}
exports.NoSanitizeAttr = NoSanitizeAttr;
class NoSpeculativeLoadHardeningAttr extends Attr {
  get kind() {
    return "NoSpeculativeLoadHardeningAttr";
  }
}
exports.NoSpeculativeLoadHardeningAttr = NoSpeculativeLoadHardeningAttr;
class NoSplitStackAttr extends Attr {
  get kind() {
    return "NoSplitStackAttr";
  }
}
exports.NoSplitStackAttr = NoSplitStackAttr;
class NoStackProtectorAttr extends Attr {
  get kind() {
    return "NoStackProtectorAttr";
  }
}
exports.NoStackProtectorAttr = NoStackProtectorAttr;
class NoThreadSafetyAnalysisAttr extends Attr {
  get kind() {
    return "NoThreadSafetyAnalysisAttr";
  }
}
exports.NoThreadSafetyAnalysisAttr = NoThreadSafetyAnalysisAttr;
class NoThrowAttr extends Attr {
  get kind() {
    return "NoThrowAttr";
  }
}
exports.NoThrowAttr = NoThrowAttr;
class NoUniqueAddressAttr extends Attr {
  get kind() {
    return "NoUniqueAddressAttr";
  }
}
exports.NoUniqueAddressAttr = NoUniqueAddressAttr;
class NotTailCalledAttr extends Attr {
  get kind() {
    return "NotTailCalledAttr";
  }
}
exports.NotTailCalledAttr = NotTailCalledAttr;
class OMPAllocateDeclAttr extends Attr {
  get kind() {
    return "OMPAllocateDeclAttr";
  }
}
exports.OMPAllocateDeclAttr = OMPAllocateDeclAttr;
class OMPCaptureNoInitAttr extends Attr {
  get kind() {
    return "OMPCaptureNoInitAttr";
  }
}
exports.OMPCaptureNoInitAttr = OMPCaptureNoInitAttr;
class OMPDeclareTargetDeclAttr extends Attr {
  get kind() {
    return "OMPDeclareTargetDeclAttr";
  }
}
exports.OMPDeclareTargetDeclAttr = OMPDeclareTargetDeclAttr;
class OMPThreadPrivateDeclAttr extends Attr {
  get kind() {
    return "OMPThreadPrivateDeclAttr";
  }
}
exports.OMPThreadPrivateDeclAttr = OMPThreadPrivateDeclAttr;
class OSConsumesThisAttr extends Attr {
  get kind() {
    return "OSConsumesThisAttr";
  }
}
exports.OSConsumesThisAttr = OSConsumesThisAttr;
class OSReturnsNotRetainedAttr extends Attr {
  get kind() {
    return "OSReturnsNotRetainedAttr";
  }
}
exports.OSReturnsNotRetainedAttr = OSReturnsNotRetainedAttr;
class OSReturnsRetainedAttr extends Attr {
  get kind() {
    return "OSReturnsRetainedAttr";
  }
}
exports.OSReturnsRetainedAttr = OSReturnsRetainedAttr;
class OSReturnsRetainedOnNonZeroAttr extends Attr {
  get kind() {
    return "OSReturnsRetainedOnNonZeroAttr";
  }
}
exports.OSReturnsRetainedOnNonZeroAttr = OSReturnsRetainedOnNonZeroAttr;
class OSReturnsRetainedOnZeroAttr extends Attr {
  get kind() {
    return "OSReturnsRetainedOnZeroAttr";
  }
}
exports.OSReturnsRetainedOnZeroAttr = OSReturnsRetainedOnZeroAttr;
class ObjCBridgeAttr extends Attr {
  get kind() {
    return "ObjCBridgeAttr";
  }
}
exports.ObjCBridgeAttr = ObjCBridgeAttr;
class ObjCBridgeMutableAttr extends Attr {
  get kind() {
    return "ObjCBridgeMutableAttr";
  }
}
exports.ObjCBridgeMutableAttr = ObjCBridgeMutableAttr;
class ObjCBridgeRelatedAttr extends Attr {
  get kind() {
    return "ObjCBridgeRelatedAttr";
  }
}
exports.ObjCBridgeRelatedAttr = ObjCBridgeRelatedAttr;
class ObjCExceptionAttr extends Attr {
  get kind() {
    return "ObjCExceptionAttr";
  }
}
exports.ObjCExceptionAttr = ObjCExceptionAttr;
class ObjCExplicitProtocolImplAttr extends Attr {
  get kind() {
    return "ObjCExplicitProtocolImplAttr";
  }
}
exports.ObjCExplicitProtocolImplAttr = ObjCExplicitProtocolImplAttr;
class ObjCExternallyRetainedAttr extends Attr {
  get kind() {
    return "ObjCExternallyRetainedAttr";
  }
}
exports.ObjCExternallyRetainedAttr = ObjCExternallyRetainedAttr;
class ObjCIndependentClassAttr extends Attr {
  get kind() {
    return "ObjCIndependentClassAttr";
  }
}
exports.ObjCIndependentClassAttr = ObjCIndependentClassAttr;
class ObjCMethodFamilyAttr extends Attr {
  get kind() {
    return "ObjCMethodFamilyAttr";
  }
}
exports.ObjCMethodFamilyAttr = ObjCMethodFamilyAttr;
class ObjCNSObjectAttr extends Attr {
  get kind() {
    return "ObjCNSObjectAttr";
  }
}
exports.ObjCNSObjectAttr = ObjCNSObjectAttr;
class ObjCPreciseLifetimeAttr extends Attr {
  get kind() {
    return "ObjCPreciseLifetimeAttr";
  }
}
exports.ObjCPreciseLifetimeAttr = ObjCPreciseLifetimeAttr;
class ObjCRequiresPropertyDefsAttr extends Attr {
  get kind() {
    return "ObjCRequiresPropertyDefsAttr";
  }
}
exports.ObjCRequiresPropertyDefsAttr = ObjCRequiresPropertyDefsAttr;
class ObjCRequiresSuperAttr extends Attr {
  get kind() {
    return "ObjCRequiresSuperAttr";
  }
}
exports.ObjCRequiresSuperAttr = ObjCRequiresSuperAttr;
class ObjCReturnsInnerPointerAttr extends Attr {
  get kind() {
    return "ObjCReturnsInnerPointerAttr";
  }
}
exports.ObjCReturnsInnerPointerAttr = ObjCReturnsInnerPointerAttr;
class ObjCRootClassAttr extends Attr {
  get kind() {
    return "ObjCRootClassAttr";
  }
}
exports.ObjCRootClassAttr = ObjCRootClassAttr;
class ObjCSubclassingRestrictedAttr extends Attr {
  get kind() {
    return "ObjCSubclassingRestrictedAttr";
  }
}
exports.ObjCSubclassingRestrictedAttr = ObjCSubclassingRestrictedAttr;
class OpenCLIntelReqdSubGroupSizeAttr extends Attr {
  get kind() {
    return "OpenCLIntelReqdSubGroupSizeAttr";
  }
}
exports.OpenCLIntelReqdSubGroupSizeAttr = OpenCLIntelReqdSubGroupSizeAttr;
class OpenCLKernelAttr extends Attr {
  get kind() {
    return "OpenCLKernelAttr";
  }
}
exports.OpenCLKernelAttr = OpenCLKernelAttr;
class OpenCLUnrollHintAttr extends Attr {
  get kind() {
    return "OpenCLUnrollHintAttr";
  }
}
exports.OpenCLUnrollHintAttr = OpenCLUnrollHintAttr;
class OptimizeNoneAttr extends Attr {
  get kind() {
    return "OptimizeNoneAttr";
  }
}
exports.OptimizeNoneAttr = OptimizeNoneAttr;
class OverrideAttr extends Attr {
  get kind() {
    return "OverrideAttr";
  }
}
exports.OverrideAttr = OverrideAttr;
class OwnerAttr extends Attr {
  get kind() {
    return "OwnerAttr";
  }
}
exports.OwnerAttr = OwnerAttr;
class OwnershipAttr extends Attr {
  get kind() {
    return "OwnershipAttr";
  }
}
exports.OwnershipAttr = OwnershipAttr;
class PackedAttr extends Attr {
  get kind() {
    return "PackedAttr";
  }
}
exports.PackedAttr = PackedAttr;
class ParamTypestateAttr extends Attr {
  get kind() {
    return "ParamTypestateAttr";
  }
}
exports.ParamTypestateAttr = ParamTypestateAttr;
class PointerAttr extends Attr {
  get kind() {
    return "PointerAttr";
  }
}
exports.PointerAttr = PointerAttr;
class PragmaClangBSSSectionAttr extends Attr {
  get kind() {
    return "PragmaClangBSSSectionAttr";
  }
}
exports.PragmaClangBSSSectionAttr = PragmaClangBSSSectionAttr;
class PragmaClangDataSectionAttr extends Attr {
  get kind() {
    return "PragmaClangDataSectionAttr";
  }
}
exports.PragmaClangDataSectionAttr = PragmaClangDataSectionAttr;
class PragmaClangRodataSectionAttr extends Attr {
  get kind() {
    return "PragmaClangRodataSectionAttr";
  }
}
exports.PragmaClangRodataSectionAttr = PragmaClangRodataSectionAttr;
class PragmaClangTextSectionAttr extends Attr {
  get kind() {
    return "PragmaClangTextSectionAttr";
  }
}
exports.PragmaClangTextSectionAttr = PragmaClangTextSectionAttr;
class PtGuardedByAttr extends Attr {
  get kind() {
    return "PtGuardedByAttr";
  }
}
exports.PtGuardedByAttr = PtGuardedByAttr;
class PtGuardedVarAttr extends Attr {
  get kind() {
    return "PtGuardedVarAttr";
  }
}
exports.PtGuardedVarAttr = PtGuardedVarAttr;
class PureAttr extends Attr {
  get kind() {
    return "PureAttr";
  }
}
exports.PureAttr = PureAttr;
class RISCVInterruptAttr extends Attr {
  get kind() {
    return "RISCVInterruptAttr";
  }
}
exports.RISCVInterruptAttr = RISCVInterruptAttr;
class ReinitializesAttr extends Attr {
  get kind() {
    return "ReinitializesAttr";
  }
}
exports.ReinitializesAttr = ReinitializesAttr;
class ReleaseCapabilityAttr extends Attr {
  get kind() {
    return "ReleaseCapabilityAttr";
  }
}
exports.ReleaseCapabilityAttr = ReleaseCapabilityAttr;
class ReqdWorkGroupSizeAttr extends Attr {
  get kind() {
    return "ReqdWorkGroupSizeAttr";
  }
}
exports.ReqdWorkGroupSizeAttr = ReqdWorkGroupSizeAttr;
class RequireConstantInitAttr extends Attr {
  get kind() {
    return "RequireConstantInitAttr";
  }
}
exports.RequireConstantInitAttr = RequireConstantInitAttr;
class RequiresCapabilityAttr extends Attr {
  get kind() {
    return "RequiresCapabilityAttr";
  }
}
exports.RequiresCapabilityAttr = RequiresCapabilityAttr;
class RestrictAttr extends Attr {
  get kind() {
    return "RestrictAttr";
  }
}
exports.RestrictAttr = RestrictAttr;
class ReturnTypestateAttr extends Attr {
  get kind() {
    return "ReturnTypestateAttr";
  }
}
exports.ReturnTypestateAttr = ReturnTypestateAttr;
class ReturnsNonNullAttr extends Attr {
  get kind() {
    return "ReturnsNonNullAttr";
  }
}
exports.ReturnsNonNullAttr = ReturnsNonNullAttr;
class ReturnsTwiceAttr extends Attr {
  get kind() {
    return "ReturnsTwiceAttr";
  }
}
exports.ReturnsTwiceAttr = ReturnsTwiceAttr;
class ScopedLockableAttr extends Attr {
  get kind() {
    return "ScopedLockableAttr";
  }
}
exports.ScopedLockableAttr = ScopedLockableAttr;
class SectionAttr extends Attr {
  get kind() {
    return "SectionAttr";
  }
}
exports.SectionAttr = SectionAttr;
class SelectAnyAttr extends Attr {
  get kind() {
    return "SelectAnyAttr";
  }
}
exports.SelectAnyAttr = SelectAnyAttr;
class SentinelAttr extends Attr {
  get kind() {
    return "SentinelAttr";
  }
}
exports.SentinelAttr = SentinelAttr;
class SetTypestateAttr extends Attr {
  get kind() {
    return "SetTypestateAttr";
  }
}
exports.SetTypestateAttr = SetTypestateAttr;
class SharedTrylockFunctionAttr extends Attr {
  get kind() {
    return "SharedTrylockFunctionAttr";
  }
}
exports.SharedTrylockFunctionAttr = SharedTrylockFunctionAttr;
class SpeculativeLoadHardeningAttr extends Attr {
  get kind() {
    return "SpeculativeLoadHardeningAttr";
  }
}
exports.SpeculativeLoadHardeningAttr = SpeculativeLoadHardeningAttr;
class TLSModelAttr extends Attr {
  get kind() {
    return "TLSModelAttr";
  }
}
exports.TLSModelAttr = TLSModelAttr;
class TargetAttr extends Attr {
  get kind() {
    return "TargetAttr";
  }
}
exports.TargetAttr = TargetAttr;
class TestTypestateAttr extends Attr {
  get kind() {
    return "TestTypestateAttr";
  }
}
exports.TestTypestateAttr = TestTypestateAttr;
class TransparentUnionAttr extends Attr {
  get kind() {
    return "TransparentUnionAttr";
  }
}
exports.TransparentUnionAttr = TransparentUnionAttr;
class TrivialABIAttr extends Attr {
  get kind() {
    return "TrivialABIAttr";
  }
}
exports.TrivialABIAttr = TrivialABIAttr;
class TryAcquireCapabilityAttr extends Attr {
  get kind() {
    return "TryAcquireCapabilityAttr";
  }
}
exports.TryAcquireCapabilityAttr = TryAcquireCapabilityAttr;
class TypeTagForDatatypeAttr extends Attr {
  get kind() {
    return "TypeTagForDatatypeAttr";
  }
}
exports.TypeTagForDatatypeAttr = TypeTagForDatatypeAttr;
class TypeVisibilityAttr extends Attr {
  get kind() {
    return "TypeVisibilityAttr";
  }
}
exports.TypeVisibilityAttr = TypeVisibilityAttr;
class UnavailableAttr extends Attr {
  get kind() {
    return "UnavailableAttr";
  }
}
exports.UnavailableAttr = UnavailableAttr;
class UninitializedAttr extends Attr {
  get kind() {
    return "UninitializedAttr";
  }
}
exports.UninitializedAttr = UninitializedAttr;
class UnusedAttr extends Attr {
  get kind() {
    return "UnusedAttr";
  }
}
exports.UnusedAttr = UnusedAttr;
class UsedAttr extends Attr {
  get kind() {
    return "UsedAttr";
  }
}
exports.UsedAttr = UsedAttr;
class UuidAttr extends Attr {
  get kind() {
    return "UuidAttr";
  }
}
exports.UuidAttr = UuidAttr;
class VecReturnAttr extends Attr {
  get kind() {
    return "VecReturnAttr";
  }
}
exports.VecReturnAttr = VecReturnAttr;
class VecTypeHintAttr extends Attr {
  get kind() {
    return "VecTypeHintAttr";
  }
}
exports.VecTypeHintAttr = VecTypeHintAttr;
class VisibilityAttr extends Attr {
  get kind() {
    return "VisibilityAttr";
  }
}
exports.VisibilityAttr = VisibilityAttr;
class WarnUnusedAttr extends Attr {
  get kind() {
    return "WarnUnusedAttr";
  }
}
exports.WarnUnusedAttr = WarnUnusedAttr;
class WarnUnusedResultAttr extends Attr {
  get kind() {
    return "WarnUnusedResultAttr";
  }
}
exports.WarnUnusedResultAttr = WarnUnusedResultAttr;
class WeakAttr extends Attr {
  get kind() {
    return "WeakAttr";
  }
}
exports.WeakAttr = WeakAttr;
class WeakImportAttr extends Attr {
  get kind() {
    return "WeakImportAttr";
  }
}
exports.WeakImportAttr = WeakImportAttr;
class WeakRefAttr extends Attr {
  get kind() {
    return "WeakRefAttr";
  }
}
exports.WeakRefAttr = WeakRefAttr;
class WebAssemblyImportModuleAttr extends Attr {
  get kind() {
    return "WebAssemblyImportModuleAttr";
  }
}
exports.WebAssemblyImportModuleAttr = WebAssemblyImportModuleAttr;
class WebAssemblyImportNameAttr extends Attr {
  get kind() {
    return "WebAssemblyImportNameAttr";
  }
}
exports.WebAssemblyImportNameAttr = WebAssemblyImportNameAttr;
class WorkGroupSizeHintAttr extends Attr {
  get kind() {
    return "WorkGroupSizeHintAttr";
  }
}
exports.WorkGroupSizeHintAttr = WorkGroupSizeHintAttr;
class X86ForceAlignArgPointerAttr extends Attr {
  get kind() {
    return "X86ForceAlignArgPointerAttr";
  }
}
exports.X86ForceAlignArgPointerAttr = X86ForceAlignArgPointerAttr;
class XRayInstrumentAttr extends Attr {
  get kind() {
    return "XRayInstrumentAttr";
  }
}
exports.XRayInstrumentAttr = XRayInstrumentAttr;
class XRayLogArgsAttr extends Attr {
  get kind() {
    return "XRayLogArgsAttr";
  }
}
exports.XRayLogArgsAttr = XRayLogArgsAttr;
class AbiTagAttr extends Attr {
  get kind() {
    return "AbiTagAttr";
  }
}
exports.AbiTagAttr = AbiTagAttr;
class AliasAttr extends Attr {
  get kind() {
    return "AliasAttr";
  }
}
exports.AliasAttr = AliasAttr;
class AlignValueAttr extends Attr {
  get kind() {
    return "AlignValueAttr";
  }
}
exports.AlignValueAttr = AlignValueAttr;
class IFuncAttr extends Attr {
  get kind() {
    return "IFuncAttr";
  }
}
exports.IFuncAttr = IFuncAttr;
class InitSegAttr extends Attr {
  get kind() {
    return "InitSegAttr";
  }
}
exports.InitSegAttr = InitSegAttr;
class LoopHintAttr extends Attr {
  get kind() {
    return "LoopHintAttr";
  }
}
exports.LoopHintAttr = LoopHintAttr;
class ModeAttr extends Attr {
  get kind() {
    return "ModeAttr";
  }
}
exports.ModeAttr = ModeAttr;
class NoEscapeAttr extends Attr {
  get kind() {
    return "NoEscapeAttr";
  }
}
exports.NoEscapeAttr = NoEscapeAttr;
class OMPCaptureKindAttr extends Attr {
  get kind() {
    return "OMPCaptureKindAttr";
  }
}
exports.OMPCaptureKindAttr = OMPCaptureKindAttr;
class OMPDeclareSimdDeclAttr extends Attr {
  get kind() {
    return "OMPDeclareSimdDeclAttr";
  }
}
exports.OMPDeclareSimdDeclAttr = OMPDeclareSimdDeclAttr;
class OMPReferencedVarAttr extends Attr {
  get kind() {
    return "OMPReferencedVarAttr";
  }
}
exports.OMPReferencedVarAttr = OMPReferencedVarAttr;
class ObjCBoxableAttr extends Attr {
  get kind() {
    return "ObjCBoxableAttr";
  }
}
exports.ObjCBoxableAttr = ObjCBoxableAttr;
class ObjCClassStubAttr extends Attr {
  get kind() {
    return "ObjCClassStubAttr";
  }
}
exports.ObjCClassStubAttr = ObjCClassStubAttr;
class ObjCDesignatedInitializerAttr extends Attr {
  get kind() {
    return "ObjCDesignatedInitializerAttr";
  }
}
exports.ObjCDesignatedInitializerAttr = ObjCDesignatedInitializerAttr;
class ObjCNonLazyClassAttr extends Attr {
  get kind() {
    return "ObjCNonLazyClassAttr";
  }
}
exports.ObjCNonLazyClassAttr = ObjCNonLazyClassAttr;
class ObjCRuntimeNameAttr extends Attr {
  get kind() {
    return "ObjCRuntimeNameAttr";
  }
}
exports.ObjCRuntimeNameAttr = ObjCRuntimeNameAttr;
class ObjCRuntimeVisibleAttr extends Attr {
  get kind() {
    return "ObjCRuntimeVisibleAttr";
  }
}
exports.ObjCRuntimeVisibleAttr = ObjCRuntimeVisibleAttr;
class OpenCLAccessAttr extends Attr {
  get kind() {
    return "OpenCLAccessAttr";
  }
}
exports.OpenCLAccessAttr = OpenCLAccessAttr;
class OverloadableAttr extends Attr {
  get kind() {
    return "OverloadableAttr";
  }
}
exports.OverloadableAttr = OverloadableAttr;
class RenderScriptKernelAttr extends Attr {
  get kind() {
    return "RenderScriptKernelAttr";
  }
}
exports.RenderScriptKernelAttr = RenderScriptKernelAttr;
class ThreadAttr extends Attr {
  get kind() {
    return "ThreadAttr";
  }
}
exports.ThreadAttr = ThreadAttr;

class Comment extends Node {
  get kind() {
    return "Comment";
  }
}
exports.Comment = Comment;

class BlockContentComment extends Comment {
  get kind() {
    return "BlockContentComment";
  }
}
exports.BlockContentComment = BlockContentComment;

class BlockCommandComment extends BlockContentComment {
  get kind() {
    return "BlockCommandComment";
  }
}
exports.BlockCommandComment = BlockCommandComment;

class ParamCommandComment extends BlockCommandComment {
  get kind() {
    return "ParamCommandComment";
  }
}
exports.ParamCommandComment = ParamCommandComment;

class TParamCommandComment extends BlockCommandComment {
  get kind() {
    return "TParamCommandComment";
  }
}
exports.TParamCommandComment = TParamCommandComment;

class VerbatimBlockComment extends BlockCommandComment {
  get kind() {
    return "VerbatimBlockComment";
  }
}
exports.VerbatimBlockComment = VerbatimBlockComment;

class VerbatimLineComment extends BlockCommandComment {
  get kind() {
    return "VerbatimLineComment";
  }
}
exports.VerbatimLineComment = VerbatimLineComment;
class ParagraphComment extends BlockContentComment {
  get kind() {
    return "ParagraphComment";
  }
}
exports.ParagraphComment = ParagraphComment;
class FullComment extends Comment {
  get kind() {
    return "FullComment";
  }
}
exports.FullComment = FullComment;

class InlineContentComment extends Comment {
  get kind() {
    return "InlineContentComment";
  }
}
exports.InlineContentComment = InlineContentComment;

class HTMLTagComment extends InlineContentComment {
  get kind() {
    return "HTMLTagComment";
  }
}
exports.HTMLTagComment = HTMLTagComment;

class HTMLEndTagComment extends HTMLTagComment {
  get kind() {
    return "HTMLEndTagComment";
  }
}
exports.HTMLEndTagComment = HTMLEndTagComment;

class HTMLStartTagComment extends HTMLTagComment {
  get kind() {
    return "HTMLStartTagComment";
  }
}
exports.HTMLStartTagComment = HTMLStartTagComment;
class InlineCommandComment extends InlineContentComment {
  get kind() {
    return "InlineCommandComment";
  }
}
exports.InlineCommandComment = InlineCommandComment;

class TextComment extends InlineContentComment {
  get kind() {
    return "TextComment";
  }
}
exports.TextComment = TextComment;
class VerbatimBlockLineComment extends Comment {
  get kind() {
    return "VerbatimBlockLineComment";
  }
}
exports.VerbatimBlockLineComment = VerbatimBlockLineComment;

class Decl extends Node {
  get kind() {
    return "Decl";
  }
}
exports.Decl = Decl;

class AccessSpecDecl extends Decl {
  get kind() {
    return "AccessSpecDecl";
  }
}
exports.AccessSpecDecl = AccessSpecDecl;

class BlockDecl extends Decl {
  get kind() {
    return "BlockDecl";
  }
}
exports.BlockDecl = BlockDecl;

class CapturedDecl extends Decl {
  get kind() {
    return "CapturedDecl";
  }
}
exports.CapturedDecl = CapturedDecl;

class ClassScopeFunctionSpecializationDecl extends Decl {
  get kind() {
    return "ClassScopeFunctionSpecializationDecl";
  }
}
exports.ClassScopeFunctionSpecializationDecl = ClassScopeFunctionSpecializationDecl;

class EmptyDecl extends Decl {
  get kind() {
    return "EmptyDecl";
  }
}
exports.EmptyDecl = EmptyDecl;

class ExportDecl extends Decl {
  get kind() {
    return "ExportDecl";
  }
}
exports.ExportDecl = ExportDecl;

class ExternCContextDecl extends Decl {
  get kind() {
    return "ExternCContextDecl";
  }
}
exports.ExternCContextDecl = ExternCContextDecl;

class FileScopeAsmDecl extends Decl {
  get kind() {
    return "FileScopeAsmDecl";
  }
}
exports.FileScopeAsmDecl = FileScopeAsmDecl;

class FriendDecl extends Decl {
  get kind() {
    return "FriendDecl";
  }
}
exports.FriendDecl = FriendDecl;

class FriendTemplateDecl extends Decl {
  get kind() {
    return "FriendTemplateDecl";
  }
}
exports.FriendTemplateDecl = FriendTemplateDecl;

class ImportDecl extends Decl {
  get kind() {
    return "ImportDecl";
  }
}
exports.ImportDecl = ImportDecl;

class LinkageSpecDecl extends Decl {
  get kind() {
    return "LinkageSpecDecl";
  }
}
exports.LinkageSpecDecl = LinkageSpecDecl;

class NamedDecl extends Decl {
  get kind() {
    return "NamedDecl";
  }
}
exports.NamedDecl = NamedDecl;

class LabelDecl extends NamedDecl {
  get kind() {
    return "LabelDecl";
  }
}
exports.LabelDecl = LabelDecl;

class NamespaceDecl extends NamedDecl {
  get kind() {
    return "NamespaceDecl";
  }
}
exports.NamespaceDecl = NamespaceDecl;

class NamespaceAliasDecl extends NamedDecl {
  get kind() {
    return "NamespaceAliasDecl";
  }
}
exports.NamespaceAliasDecl = NamespaceAliasDecl;

class ObjCCompatibleAliasDecl extends NamedDecl {
  get kind() {
    return "ObjCCompatibleAliasDecl";
  }
}
exports.ObjCCompatibleAliasDecl = ObjCCompatibleAliasDecl;

class ObjCContainerDecl extends NamedDecl {
  get kind() {
    return "ObjCContainerDecl";
  }
}
exports.ObjCContainerDecl = ObjCContainerDecl;

class ObjCCategoryDecl extends ObjCContainerDecl {
  get kind() {
    return "ObjCCategoryDecl";
  }
}
exports.ObjCCategoryDecl = ObjCCategoryDecl;

class ObjCImplDecl extends ObjCContainerDecl {
  get kind() {
    return "ObjCImplDecl";
  }
}
exports.ObjCImplDecl = ObjCImplDecl;

class ObjCCategoryImplDecl extends ObjCImplDecl {
  get kind() {
    return "ObjCCategoryImplDecl";
  }
}
exports.ObjCCategoryImplDecl = ObjCCategoryImplDecl;

class ObjCImplementationDecl extends ObjCImplDecl {
  get kind() {
    return "ObjCImplementationDecl";
  }
}
exports.ObjCImplementationDecl = ObjCImplementationDecl;
class ObjCInterfaceDecl extends ObjCContainerDecl {
  get kind() {
    return "ObjCInterfaceDecl";
  }
}
exports.ObjCInterfaceDecl = ObjCInterfaceDecl;

class ObjCProtocolDecl extends ObjCContainerDecl {
  get kind() {
    return "ObjCProtocolDecl";
  }
}
exports.ObjCProtocolDecl = ObjCProtocolDecl;
class ObjCMethodDecl extends NamedDecl {
  get kind() {
    return "ObjCMethodDecl";
  }
}
exports.ObjCMethodDecl = ObjCMethodDecl;

class ObjCPropertyDecl extends NamedDecl {
  get kind() {
    return "ObjCPropertyDecl";
  }
}
exports.ObjCPropertyDecl = ObjCPropertyDecl;

class TemplateDecl extends NamedDecl {
  get kind() {
    return "TemplateDecl";
  }
}
exports.TemplateDecl = TemplateDecl;

class BuiltinTemplateDecl extends TemplateDecl {
  get kind() {
    return "BuiltinTemplateDecl";
  }
}
exports.BuiltinTemplateDecl = BuiltinTemplateDecl;

class ConceptDecl extends TemplateDecl {
  get kind() {
    return "ConceptDecl";
  }
}
exports.ConceptDecl = ConceptDecl;

class RedeclarableTemplateDecl extends TemplateDecl {
  get kind() {
    return "RedeclarableTemplateDecl";
  }
}
exports.RedeclarableTemplateDecl = RedeclarableTemplateDecl;

class ClassTemplateDecl extends RedeclarableTemplateDecl {
  get kind() {
    return "ClassTemplateDecl";
  }
}
exports.ClassTemplateDecl = ClassTemplateDecl;

class FunctionTemplateDecl extends RedeclarableTemplateDecl {
  get kind() {
    return "FunctionTemplateDecl";
  }
}
exports.FunctionTemplateDecl = FunctionTemplateDecl;

class TypeAliasTemplateDecl extends RedeclarableTemplateDecl {
  get kind() {
    return "TypeAliasTemplateDecl";
  }
}
exports.TypeAliasTemplateDecl = TypeAliasTemplateDecl;

class VarTemplateDecl extends RedeclarableTemplateDecl {
  get kind() {
    return "VarTemplateDecl";
  }
}
exports.VarTemplateDecl = VarTemplateDecl;
class TemplateTemplateParmDecl extends TemplateDecl {
  get kind() {
    return "TemplateTemplateParmDecl";
  }
}
exports.TemplateTemplateParmDecl = TemplateTemplateParmDecl;
class TypeDecl extends NamedDecl {
  get kind() {
    return "TypeDecl";
  }
}
exports.TypeDecl = TypeDecl;

class TagDecl extends TypeDecl {
  get kind() {
    return "TagDecl";
  }
}
exports.TagDecl = TagDecl;

class EnumDecl extends TagDecl {
  get kind() {
    return "EnumDecl";
  }
}
exports.EnumDecl = EnumDecl;

class RecordDecl extends TagDecl {
  get kind() {
    return "RecordDecl";
  }
}
exports.RecordDecl = RecordDecl;

class CXXRecordDecl extends RecordDecl {
  get kind() {
    return "CXXRecordDecl";
  }
}
exports.CXXRecordDecl = CXXRecordDecl;

class ClassTemplateSpecializationDecl extends CXXRecordDecl {
  get kind() {
    return "ClassTemplateSpecializationDecl";
  }
}
exports.ClassTemplateSpecializationDecl = ClassTemplateSpecializationDecl;

class ClassTemplatePartialSpecializationDecl extends ClassTemplateSpecializationDecl {
  get kind() {
    return "ClassTemplatePartialSpecializationDecl";
  }
}
exports.ClassTemplatePartialSpecializationDecl = ClassTemplatePartialSpecializationDecl;
class TemplateTypeParmDecl extends TypeDecl {
  get kind() {
    return "TemplateTypeParmDecl";
  }
}
exports.TemplateTypeParmDecl = TemplateTypeParmDecl;

class TypedefNameDecl extends TypeDecl {
  get kind() {
    return "TypedefNameDecl";
  }
}
exports.TypedefNameDecl = TypedefNameDecl;

class ObjCTypeParamDecl extends TypedefNameDecl {
  get kind() {
    return "ObjCTypeParamDecl";
  }
}
exports.ObjCTypeParamDecl = ObjCTypeParamDecl;

class TypeAliasDecl extends TypedefNameDecl {
  get kind() {
    return "TypeAliasDecl";
  }
}
exports.TypeAliasDecl = TypeAliasDecl;

class TypedefDecl extends TypedefNameDecl {
  get kind() {
    return "TypedefDecl";
  }
}
exports.TypedefDecl = TypedefDecl;
class UnresolvedUsingTypenameDecl extends TypeDecl {
  get kind() {
    return "UnresolvedUsingTypenameDecl";
  }
}
exports.UnresolvedUsingTypenameDecl = UnresolvedUsingTypenameDecl;
class UsingDecl extends NamedDecl {
  get kind() {
    return "UsingDecl";
  }
}
exports.UsingDecl = UsingDecl;

class UsingDirectiveDecl extends NamedDecl {
  get kind() {
    return "UsingDirectiveDecl";
  }
}
exports.UsingDirectiveDecl = UsingDirectiveDecl;

class UsingPackDecl extends NamedDecl {
  get kind() {
    return "UsingPackDecl";
  }
}
exports.UsingPackDecl = UsingPackDecl;

class UsingShadowDecl extends NamedDecl {
  get kind() {
    return "UsingShadowDecl";
  }
}
exports.UsingShadowDecl = UsingShadowDecl;

class ConstructorUsingShadowDecl extends UsingShadowDecl {
  get kind() {
    return "ConstructorUsingShadowDecl";
  }
}
exports.ConstructorUsingShadowDecl = ConstructorUsingShadowDecl;
class ValueDecl extends NamedDecl {
  get kind() {
    return "ValueDecl";
  }
}
exports.ValueDecl = ValueDecl;

class BindingDecl extends ValueDecl {
  get kind() {
    return "BindingDecl";
  }
}
exports.BindingDecl = BindingDecl;

class DeclaratorDecl extends ValueDecl {
  get kind() {
    return "DeclaratorDecl";
  }
}
exports.DeclaratorDecl = DeclaratorDecl;

class FieldDecl extends DeclaratorDecl {
  get kind() {
    return "FieldDecl";
  }
}
exports.FieldDecl = FieldDecl;

class ObjCAtDefsFieldDecl extends FieldDecl {
  get kind() {
    return "ObjCAtDefsFieldDecl";
  }
}
exports.ObjCAtDefsFieldDecl = ObjCAtDefsFieldDecl;

class ObjCIvarDecl extends FieldDecl {
  get kind() {
    return "ObjCIvarDecl";
  }
}
exports.ObjCIvarDecl = ObjCIvarDecl;
class FunctionDecl extends DeclaratorDecl {
  get kind() {
    return "FunctionDecl";
  }
}
exports.FunctionDecl = FunctionDecl;

class CXXDeductionGuideDecl extends FunctionDecl {
  get kind() {
    return "CXXDeductionGuideDecl";
  }
}
exports.CXXDeductionGuideDecl = CXXDeductionGuideDecl;

class CXXMethodDecl extends FunctionDecl {
  get kind() {
    return "CXXMethodDecl";
  }
}
exports.CXXMethodDecl = CXXMethodDecl;

class CXXConstructorDecl extends CXXMethodDecl {
  get kind() {
    return "CXXConstructorDecl";
  }
}
exports.CXXConstructorDecl = CXXConstructorDecl;

class CXXConversionDecl extends CXXMethodDecl {
  get kind() {
    return "CXXConversionDecl";
  }
}
exports.CXXConversionDecl = CXXConversionDecl;

class CXXDestructorDecl extends CXXMethodDecl {
  get kind() {
    return "CXXDestructorDecl";
  }
}
exports.CXXDestructorDecl = CXXDestructorDecl;
class MSPropertyDecl extends DeclaratorDecl {
  get kind() {
    return "MSPropertyDecl";
  }
}
exports.MSPropertyDecl = MSPropertyDecl;

class NonTypeTemplateParmDecl extends DeclaratorDecl {
  get kind() {
    return "NonTypeTemplateParmDecl";
  }
}
exports.NonTypeTemplateParmDecl = NonTypeTemplateParmDecl;

class VarDecl extends DeclaratorDecl {
  get kind() {
    return "VarDecl";
  }
}
exports.VarDecl = VarDecl;

class DecompositionDecl extends VarDecl {
  get kind() {
    return "DecompositionDecl";
  }
}
exports.DecompositionDecl = DecompositionDecl;

class ImplicitParamDecl extends VarDecl {
  get kind() {
    return "ImplicitParamDecl";
  }
}
exports.ImplicitParamDecl = ImplicitParamDecl;

class OMPCapturedExprDecl extends VarDecl {
  get kind() {
    return "OMPCapturedExprDecl";
  }
}
exports.OMPCapturedExprDecl = OMPCapturedExprDecl;

class ParmVarDecl extends VarDecl {
  get kind() {
    return "ParmVarDecl";
  }
}
exports.ParmVarDecl = ParmVarDecl;

class VarTemplateSpecializationDecl extends VarDecl {
  get kind() {
    return "VarTemplateSpecializationDecl";
  }
}
exports.VarTemplateSpecializationDecl = VarTemplateSpecializationDecl;

class VarTemplatePartialSpecializationDecl extends VarTemplateSpecializationDecl {
  get kind() {
    return "VarTemplatePartialSpecializationDecl";
  }
}
exports.VarTemplatePartialSpecializationDecl = VarTemplatePartialSpecializationDecl;
class EnumConstantDecl extends ValueDecl {
  get kind() {
    return "EnumConstantDecl";
  }
}
exports.EnumConstantDecl = EnumConstantDecl;

class IndirectFieldDecl extends ValueDecl {
  get kind() {
    return "IndirectFieldDecl";
  }
}
exports.IndirectFieldDecl = IndirectFieldDecl;

class OMPDeclareMapperDecl extends ValueDecl {
  get kind() {
    return "OMPDeclareMapperDecl";
  }
}
exports.OMPDeclareMapperDecl = OMPDeclareMapperDecl;

class OMPDeclareReductionDecl extends ValueDecl {
  get kind() {
    return "OMPDeclareReductionDecl";
  }
}
exports.OMPDeclareReductionDecl = OMPDeclareReductionDecl;

class UnresolvedUsingValueDecl extends ValueDecl {
  get kind() {
    return "UnresolvedUsingValueDecl";
  }
}
exports.UnresolvedUsingValueDecl = UnresolvedUsingValueDecl;
class OMPAllocateDecl extends Decl {
  get kind() {
    return "OMPAllocateDecl";
  }
}
exports.OMPAllocateDecl = OMPAllocateDecl;

class OMPRequiresDecl extends Decl {
  get kind() {
    return "OMPRequiresDecl";
  }
}
exports.OMPRequiresDecl = OMPRequiresDecl;

class OMPThreadPrivateDecl extends Decl {
  get kind() {
    return "OMPThreadPrivateDecl";
  }
}
exports.OMPThreadPrivateDecl = OMPThreadPrivateDecl;

class ObjCPropertyImplDecl extends Decl {
  get kind() {
    return "ObjCPropertyImplDecl";
  }
}
exports.ObjCPropertyImplDecl = ObjCPropertyImplDecl;

class PragmaCommentDecl extends Decl {
  get kind() {
    return "PragmaCommentDecl";
  }
}
exports.PragmaCommentDecl = PragmaCommentDecl;

class PragmaDetectMismatchDecl extends Decl {
  get kind() {
    return "PragmaDetectMismatchDecl";
  }
}
exports.PragmaDetectMismatchDecl = PragmaDetectMismatchDecl;

class StaticAssertDecl extends Decl {
  get kind() {
    return "StaticAssertDecl";
  }
}
exports.StaticAssertDecl = StaticAssertDecl;

class TranslationUnitDecl extends Decl {
  get kind() {
    return "TranslationUnitDecl";
  }
}
exports.TranslationUnitDecl = TranslationUnitDecl;

class Stmt extends Node {
  get kind() {
    return "Stmt";
  }
}
exports.Stmt = Stmt;

class AsmStmt extends Stmt {
  get kind() {
    return "AsmStmt";
  }
}
exports.AsmStmt = AsmStmt;

class GCCAsmStmt extends AsmStmt {
  get kind() {
    return "GCCAsmStmt";
  }
}
exports.GCCAsmStmt = GCCAsmStmt;

class MSAsmStmt extends AsmStmt {
  get kind() {
    return "MSAsmStmt";
  }
}
exports.MSAsmStmt = MSAsmStmt;
class BreakStmt extends Stmt {
  get kind() {
    return "BreakStmt";
  }
}
exports.BreakStmt = BreakStmt;

class CXXCatchStmt extends Stmt {
  get kind() {
    return "CXXCatchStmt";
  }
}
exports.CXXCatchStmt = CXXCatchStmt;

class CXXForRangeStmt extends Stmt {
  get kind() {
    return "CXXForRangeStmt";
  }
}
exports.CXXForRangeStmt = CXXForRangeStmt;

class CXXTryStmt extends Stmt {
  get kind() {
    return "CXXTryStmt";
  }
}
exports.CXXTryStmt = CXXTryStmt;

class CapturedStmt extends Stmt {
  get kind() {
    return "CapturedStmt";
  }
}
exports.CapturedStmt = CapturedStmt;

class CompoundStmt extends Stmt {
  get kind() {
    return "CompoundStmt";
  }
}
exports.CompoundStmt = CompoundStmt;

class ContinueStmt extends Stmt {
  get kind() {
    return "ContinueStmt";
  }
}
exports.ContinueStmt = ContinueStmt;

class CoreturnStmt extends Stmt {
  get kind() {
    return "CoreturnStmt";
  }
}
exports.CoreturnStmt = CoreturnStmt;

class CoroutineBodyStmt extends Stmt {
  get kind() {
    return "CoroutineBodyStmt";
  }
}
exports.CoroutineBodyStmt = CoroutineBodyStmt;

class DeclStmt extends Stmt {
  get kind() {
    return "DeclStmt";
  }
}
exports.DeclStmt = DeclStmt;

class DoStmt extends Stmt {
  get kind() {
    return "DoStmt";
  }
}
exports.DoStmt = DoStmt;

class ForStmt extends Stmt {
  get kind() {
    return "ForStmt";
  }
}
exports.ForStmt = ForStmt;

class GotoStmt extends Stmt {
  get kind() {
    return "GotoStmt";
  }
}
exports.GotoStmt = GotoStmt;

class IfStmt extends Stmt {
  get kind() {
    return "IfStmt";
  }
}
exports.IfStmt = IfStmt;

class IndirectGotoStmt extends Stmt {
  get kind() {
    return "IndirectGotoStmt";
  }
}
exports.IndirectGotoStmt = IndirectGotoStmt;

class MSDependentExistsStmt extends Stmt {
  get kind() {
    return "MSDependentExistsStmt";
  }
}
exports.MSDependentExistsStmt = MSDependentExistsStmt;

class NullStmt extends Stmt {
  get kind() {
    return "NullStmt";
  }
}
exports.NullStmt = NullStmt;

class OMPExecutableDirective extends Stmt {
  get kind() {
    return "OMPExecutableDirective";
  }
}
exports.OMPExecutableDirective = OMPExecutableDirective;

class OMPAtomicDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPAtomicDirective";
  }
}
exports.OMPAtomicDirective = OMPAtomicDirective;

class OMPBarrierDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPBarrierDirective";
  }
}
exports.OMPBarrierDirective = OMPBarrierDirective;

class OMPCancelDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPCancelDirective";
  }
}
exports.OMPCancelDirective = OMPCancelDirective;

class OMPCancellationPointDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPCancellationPointDirective";
  }
}
exports.OMPCancellationPointDirective = OMPCancellationPointDirective;

class OMPCriticalDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPCriticalDirective";
  }
}
exports.OMPCriticalDirective = OMPCriticalDirective;

class OMPFlushDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPFlushDirective";
  }
}
exports.OMPFlushDirective = OMPFlushDirective;

class OMPLoopDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPLoopDirective";
  }
}
exports.OMPLoopDirective = OMPLoopDirective;

class OMPDistributeDirective extends OMPLoopDirective {
  get kind() {
    return "OMPDistributeDirective";
  }
}
exports.OMPDistributeDirective = OMPDistributeDirective;

class OMPDistributeParallelForDirective extends OMPLoopDirective {
  get kind() {
    return "OMPDistributeParallelForDirective";
  }
}
exports.OMPDistributeParallelForDirective = OMPDistributeParallelForDirective;

class OMPDistributeParallelForSimdDirective extends OMPLoopDirective {
  get kind() {
    return "OMPDistributeParallelForSimdDirective";
  }
}
exports.OMPDistributeParallelForSimdDirective = OMPDistributeParallelForSimdDirective;

class OMPDistributeSimdDirective extends OMPLoopDirective {
  get kind() {
    return "OMPDistributeSimdDirective";
  }
}
exports.OMPDistributeSimdDirective = OMPDistributeSimdDirective;

class OMPForDirective extends OMPLoopDirective {
  get kind() {
    return "OMPForDirective";
  }
}
exports.OMPForDirective = OMPForDirective;

class OMPForSimdDirective extends OMPLoopDirective {
  get kind() {
    return "OMPForSimdDirective";
  }
}
exports.OMPForSimdDirective = OMPForSimdDirective;

class OMPParallelForDirective extends OMPLoopDirective {
  get kind() {
    return "OMPParallelForDirective";
  }
}
exports.OMPParallelForDirective = OMPParallelForDirective;

class OMPParallelForSimdDirective extends OMPLoopDirective {
  get kind() {
    return "OMPParallelForSimdDirective";
  }
}
exports.OMPParallelForSimdDirective = OMPParallelForSimdDirective;

class OMPSimdDirective extends OMPLoopDirective {
  get kind() {
    return "OMPSimdDirective";
  }
}
exports.OMPSimdDirective = OMPSimdDirective;

class OMPTargetParallelForSimdDirective extends OMPLoopDirective {
  get kind() {
    return "OMPTargetParallelForSimdDirective";
  }
}
exports.OMPTargetParallelForSimdDirective = OMPTargetParallelForSimdDirective;

class OMPTargetSimdDirective extends OMPLoopDirective {
  get kind() {
    return "OMPTargetSimdDirective";
  }
}
exports.OMPTargetSimdDirective = OMPTargetSimdDirective;

class OMPTargetTeamsDistributeDirective extends OMPLoopDirective {
  get kind() {
    return "OMPTargetTeamsDistributeDirective";
  }
}
exports.OMPTargetTeamsDistributeDirective = OMPTargetTeamsDistributeDirective;

class OMPTargetTeamsDistributeParallelForDirective extends OMPLoopDirective {
  get kind() {
    return "OMPTargetTeamsDistributeParallelForDirective";
  }
}
exports.OMPTargetTeamsDistributeParallelForDirective = OMPTargetTeamsDistributeParallelForDirective;

class OMPTargetTeamsDistributeParallelForSimdDirective extends OMPLoopDirective {
  get kind() {
    return "OMPTargetTeamsDistributeParallelForSimdDirective";
  }
}
exports.OMPTargetTeamsDistributeParallelForSimdDirective = OMPTargetTeamsDistributeParallelForSimdDirective;

class OMPTargetTeamsDistributeSimdDirective extends OMPLoopDirective {
  get kind() {
    return "OMPTargetTeamsDistributeSimdDirective";
  }
}
exports.OMPTargetTeamsDistributeSimdDirective = OMPTargetTeamsDistributeSimdDirective;

class OMPTaskLoopDirective extends OMPLoopDirective {
  get kind() {
    return "OMPTaskLoopDirective";
  }
}
exports.OMPTaskLoopDirective = OMPTaskLoopDirective;

class OMPTaskLoopSimdDirective extends OMPLoopDirective {
  get kind() {
    return "OMPTaskLoopSimdDirective";
  }
}
exports.OMPTaskLoopSimdDirective = OMPTaskLoopSimdDirective;

class OMPTeamsDistributeDirective extends OMPLoopDirective {
  get kind() {
    return "OMPTeamsDistributeDirective";
  }
}
exports.OMPTeamsDistributeDirective = OMPTeamsDistributeDirective;

class OMPTeamsDistributeParallelForDirective extends OMPLoopDirective {
  get kind() {
    return "OMPTeamsDistributeParallelForDirective";
  }
}
exports.OMPTeamsDistributeParallelForDirective = OMPTeamsDistributeParallelForDirective;

class OMPTeamsDistributeParallelForSimdDirective extends OMPLoopDirective {
  get kind() {
    return "OMPTeamsDistributeParallelForSimdDirective";
  }
}
exports.OMPTeamsDistributeParallelForSimdDirective = OMPTeamsDistributeParallelForSimdDirective;

class OMPTeamsDistributeSimdDirective extends OMPLoopDirective {
  get kind() {
    return "OMPTeamsDistributeSimdDirective";
  }
}
exports.OMPTeamsDistributeSimdDirective = OMPTeamsDistributeSimdDirective;
class OMPMasterDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPMasterDirective";
  }
}
exports.OMPMasterDirective = OMPMasterDirective;

class OMPOrderedDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPOrderedDirective";
  }
}
exports.OMPOrderedDirective = OMPOrderedDirective;

class OMPParallelDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPParallelDirective";
  }
}
exports.OMPParallelDirective = OMPParallelDirective;

class OMPParallelSectionsDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPParallelSectionsDirective";
  }
}
exports.OMPParallelSectionsDirective = OMPParallelSectionsDirective;

class OMPSectionDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPSectionDirective";
  }
}
exports.OMPSectionDirective = OMPSectionDirective;

class OMPSectionsDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPSectionsDirective";
  }
}
exports.OMPSectionsDirective = OMPSectionsDirective;

class OMPSingleDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPSingleDirective";
  }
}
exports.OMPSingleDirective = OMPSingleDirective;

class OMPTargetDataDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPTargetDataDirective";
  }
}
exports.OMPTargetDataDirective = OMPTargetDataDirective;

class OMPTargetDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPTargetDirective";
  }
}
exports.OMPTargetDirective = OMPTargetDirective;

class OMPTargetEnterDataDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPTargetEnterDataDirective";
  }
}
exports.OMPTargetEnterDataDirective = OMPTargetEnterDataDirective;

class OMPTargetExitDataDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPTargetExitDataDirective";
  }
}
exports.OMPTargetExitDataDirective = OMPTargetExitDataDirective;

class OMPTargetParallelDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPTargetParallelDirective";
  }
}
exports.OMPTargetParallelDirective = OMPTargetParallelDirective;

class OMPTargetParallelForDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPTargetParallelForDirective";
  }
}
exports.OMPTargetParallelForDirective = OMPTargetParallelForDirective;

class OMPTargetTeamsDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPTargetTeamsDirective";
  }
}
exports.OMPTargetTeamsDirective = OMPTargetTeamsDirective;

class OMPTargetUpdateDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPTargetUpdateDirective";
  }
}
exports.OMPTargetUpdateDirective = OMPTargetUpdateDirective;

class OMPTaskDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPTaskDirective";
  }
}
exports.OMPTaskDirective = OMPTaskDirective;

class OMPTaskgroupDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPTaskgroupDirective";
  }
}
exports.OMPTaskgroupDirective = OMPTaskgroupDirective;

class OMPTaskwaitDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPTaskwaitDirective";
  }
}
exports.OMPTaskwaitDirective = OMPTaskwaitDirective;

class OMPTaskyieldDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPTaskyieldDirective";
  }
}
exports.OMPTaskyieldDirective = OMPTaskyieldDirective;

class OMPTeamsDirective extends OMPExecutableDirective {
  get kind() {
    return "OMPTeamsDirective";
  }
}
exports.OMPTeamsDirective = OMPTeamsDirective;
class ObjCAtCatchStmt extends Stmt {
  get kind() {
    return "ObjCAtCatchStmt";
  }
}
exports.ObjCAtCatchStmt = ObjCAtCatchStmt;

class ObjCAtFinallyStmt extends Stmt {
  get kind() {
    return "ObjCAtFinallyStmt";
  }
}
exports.ObjCAtFinallyStmt = ObjCAtFinallyStmt;

class ObjCAtSynchronizedStmt extends Stmt {
  get kind() {
    return "ObjCAtSynchronizedStmt";
  }
}
exports.ObjCAtSynchronizedStmt = ObjCAtSynchronizedStmt;

class ObjCAtThrowStmt extends Stmt {
  get kind() {
    return "ObjCAtThrowStmt";
  }
}
exports.ObjCAtThrowStmt = ObjCAtThrowStmt;

class ObjCAtTryStmt extends Stmt {
  get kind() {
    return "ObjCAtTryStmt";
  }
}
exports.ObjCAtTryStmt = ObjCAtTryStmt;

class ObjCAutoreleasePoolStmt extends Stmt {
  get kind() {
    return "ObjCAutoreleasePoolStmt";
  }
}
exports.ObjCAutoreleasePoolStmt = ObjCAutoreleasePoolStmt;

class ObjCForCollectionStmt extends Stmt {
  get kind() {
    return "ObjCForCollectionStmt";
  }
}
exports.ObjCForCollectionStmt = ObjCForCollectionStmt;

class ReturnStmt extends Stmt {
  get kind() {
    return "ReturnStmt";
  }
}
exports.ReturnStmt = ReturnStmt;

class SEHExceptStmt extends Stmt {
  get kind() {
    return "SEHExceptStmt";
  }
}
exports.SEHExceptStmt = SEHExceptStmt;

class SEHFinallyStmt extends Stmt {
  get kind() {
    return "SEHFinallyStmt";
  }
}
exports.SEHFinallyStmt = SEHFinallyStmt;

class SEHLeaveStmt extends Stmt {
  get kind() {
    return "SEHLeaveStmt";
  }
}
exports.SEHLeaveStmt = SEHLeaveStmt;

class SEHTryStmt extends Stmt {
  get kind() {
    return "SEHTryStmt";
  }
}
exports.SEHTryStmt = SEHTryStmt;

class SwitchCase extends Stmt {
  get kind() {
    return "SwitchCase";
  }
}
exports.SwitchCase = SwitchCase;

class CaseStmt extends SwitchCase {
  get kind() {
    return "CaseStmt";
  }
}
exports.CaseStmt = CaseStmt;

class DefaultStmt extends SwitchCase {
  get kind() {
    return "DefaultStmt";
  }
}
exports.DefaultStmt = DefaultStmt;
class SwitchStmt extends Stmt {
  get kind() {
    return "SwitchStmt";
  }
}
exports.SwitchStmt = SwitchStmt;

class ValueStmt extends Stmt {
  get kind() {
    return "ValueStmt";
  }
}
exports.ValueStmt = ValueStmt;

class AttributedStmt extends ValueStmt {
  get kind() {
    return "AttributedStmt";
  }
}
exports.AttributedStmt = AttributedStmt;

class Expr extends ValueStmt {
  get kind() {
    return "Expr";
  }
}
exports.Expr = Expr;

class AbstractConditionalOperator extends Expr {
  get kind() {
    return "AbstractConditionalOperator";
  }
}
exports.AbstractConditionalOperator = AbstractConditionalOperator;

class BinaryConditionalOperator extends AbstractConditionalOperator {
  get kind() {
    return "BinaryConditionalOperator";
  }
}
exports.BinaryConditionalOperator = BinaryConditionalOperator;

class ConditionalOperator extends AbstractConditionalOperator {
  get kind() {
    return "ConditionalOperator";
  }
}
exports.ConditionalOperator = ConditionalOperator;
class AddrLabelExpr extends Expr {
  get kind() {
    return "AddrLabelExpr";
  }
}
exports.AddrLabelExpr = AddrLabelExpr;

class ArrayInitIndexExpr extends Expr {
  get kind() {
    return "ArrayInitIndexExpr";
  }
}
exports.ArrayInitIndexExpr = ArrayInitIndexExpr;

class ArrayInitLoopExpr extends Expr {
  get kind() {
    return "ArrayInitLoopExpr";
  }
}
exports.ArrayInitLoopExpr = ArrayInitLoopExpr;

class ArraySubscriptExpr extends Expr {
  get kind() {
    return "ArraySubscriptExpr";
  }
}
exports.ArraySubscriptExpr = ArraySubscriptExpr;

class ArrayTypeTraitExpr extends Expr {
  get kind() {
    return "ArrayTypeTraitExpr";
  }
}
exports.ArrayTypeTraitExpr = ArrayTypeTraitExpr;

class AsTypeExpr extends Expr {
  get kind() {
    return "AsTypeExpr";
  }
}
exports.AsTypeExpr = AsTypeExpr;

class AtomicExpr extends Expr {
  get kind() {
    return "AtomicExpr";
  }
}
exports.AtomicExpr = AtomicExpr;

class BinaryOperator extends Expr {
  get kind() {
    return "BinaryOperator";
  }
}
exports.BinaryOperator = BinaryOperator;

class CompoundAssignOperator extends BinaryOperator {
  get kind() {
    return "CompoundAssignOperator";
  }
}
exports.CompoundAssignOperator = CompoundAssignOperator;
class BlockExpr extends Expr {
  get kind() {
    return "BlockExpr";
  }
}
exports.BlockExpr = BlockExpr;

class CXXBindTemporaryExpr extends Expr {
  get kind() {
    return "CXXBindTemporaryExpr";
  }
}
exports.CXXBindTemporaryExpr = CXXBindTemporaryExpr;

class CXXBoolLiteralExpr extends Expr {
  get kind() {
    return "CXXBoolLiteralExpr";
  }
}
exports.CXXBoolLiteralExpr = CXXBoolLiteralExpr;

class CXXConstructExpr extends Expr {
  get kind() {
    return "CXXConstructExpr";
  }
}
exports.CXXConstructExpr = CXXConstructExpr;

class CXXTemporaryObjectExpr extends CXXConstructExpr {
  get kind() {
    return "CXXTemporaryObjectExpr";
  }
}
exports.CXXTemporaryObjectExpr = CXXTemporaryObjectExpr;
class CXXDefaultArgExpr extends Expr {
  get kind() {
    return "CXXDefaultArgExpr";
  }
}
exports.CXXDefaultArgExpr = CXXDefaultArgExpr;

class CXXDefaultInitExpr extends Expr {
  get kind() {
    return "CXXDefaultInitExpr";
  }
}
exports.CXXDefaultInitExpr = CXXDefaultInitExpr;

class CXXDeleteExpr extends Expr {
  get kind() {
    return "CXXDeleteExpr";
  }
}
exports.CXXDeleteExpr = CXXDeleteExpr;

class CXXDependentScopeMemberExpr extends Expr {
  get kind() {
    return "CXXDependentScopeMemberExpr";
  }
}
exports.CXXDependentScopeMemberExpr = CXXDependentScopeMemberExpr;

class CXXFoldExpr extends Expr {
  get kind() {
    return "CXXFoldExpr";
  }
}
exports.CXXFoldExpr = CXXFoldExpr;

class CXXInheritedCtorInitExpr extends Expr {
  get kind() {
    return "CXXInheritedCtorInitExpr";
  }
}
exports.CXXInheritedCtorInitExpr = CXXInheritedCtorInitExpr;

class CXXNewExpr extends Expr {
  get kind() {
    return "CXXNewExpr";
  }
}
exports.CXXNewExpr = CXXNewExpr;

class CXXNoexceptExpr extends Expr {
  get kind() {
    return "CXXNoexceptExpr";
  }
}
exports.CXXNoexceptExpr = CXXNoexceptExpr;

class CXXNullPtrLiteralExpr extends Expr {
  get kind() {
    return "CXXNullPtrLiteralExpr";
  }
}
exports.CXXNullPtrLiteralExpr = CXXNullPtrLiteralExpr;

class CXXPseudoDestructorExpr extends Expr {
  get kind() {
    return "CXXPseudoDestructorExpr";
  }
}
exports.CXXPseudoDestructorExpr = CXXPseudoDestructorExpr;

class CXXScalarValueInitExpr extends Expr {
  get kind() {
    return "CXXScalarValueInitExpr";
  }
}
exports.CXXScalarValueInitExpr = CXXScalarValueInitExpr;

class CXXStdInitializerListExpr extends Expr {
  get kind() {
    return "CXXStdInitializerListExpr";
  }
}
exports.CXXStdInitializerListExpr = CXXStdInitializerListExpr;

class CXXThisExpr extends Expr {
  get kind() {
    return "CXXThisExpr";
  }
}
exports.CXXThisExpr = CXXThisExpr;

class CXXThrowExpr extends Expr {
  get kind() {
    return "CXXThrowExpr";
  }
}
exports.CXXThrowExpr = CXXThrowExpr;

class CXXTypeidExpr extends Expr {
  get kind() {
    return "CXXTypeidExpr";
  }
}
exports.CXXTypeidExpr = CXXTypeidExpr;

class CXXUnresolvedConstructExpr extends Expr {
  get kind() {
    return "CXXUnresolvedConstructExpr";
  }
}
exports.CXXUnresolvedConstructExpr = CXXUnresolvedConstructExpr;

class CXXUuidofExpr extends Expr {
  get kind() {
    return "CXXUuidofExpr";
  }
}
exports.CXXUuidofExpr = CXXUuidofExpr;

class CallExpr extends Expr {
  get kind() {
    return "CallExpr";
  }
}
exports.CallExpr = CallExpr;

class CUDAKernelCallExpr extends CallExpr {
  get kind() {
    return "CUDAKernelCallExpr";
  }
}
exports.CUDAKernelCallExpr = CUDAKernelCallExpr;

class CXXMemberCallExpr extends CallExpr {
  get kind() {
    return "CXXMemberCallExpr";
  }
}
exports.CXXMemberCallExpr = CXXMemberCallExpr;

class CXXOperatorCallExpr extends CallExpr {
  get kind() {
    return "CXXOperatorCallExpr";
  }
}
exports.CXXOperatorCallExpr = CXXOperatorCallExpr;

class UserDefinedLiteral extends CallExpr {
  get kind() {
    return "UserDefinedLiteral";
  }
}
exports.UserDefinedLiteral = UserDefinedLiteral;
class CastExpr extends Expr {
  get kind() {
    return "CastExpr";
  }
}
exports.CastExpr = CastExpr;

class ExplicitCastExpr extends CastExpr {
  get kind() {
    return "ExplicitCastExpr";
  }
}
exports.ExplicitCastExpr = ExplicitCastExpr;

class BuiltinBitCastExpr extends ExplicitCastExpr {
  get kind() {
    return "BuiltinBitCastExpr";
  }
}
exports.BuiltinBitCastExpr = BuiltinBitCastExpr;

class CStyleCastExpr extends ExplicitCastExpr {
  get kind() {
    return "CStyleCastExpr";
  }
}
exports.CStyleCastExpr = CStyleCastExpr;

class CXXFunctionalCastExpr extends ExplicitCastExpr {
  get kind() {
    return "CXXFunctionalCastExpr";
  }
}
exports.CXXFunctionalCastExpr = CXXFunctionalCastExpr;

class CXXNamedCastExpr extends ExplicitCastExpr {
  get kind() {
    return "CXXNamedCastExpr";
  }
}
exports.CXXNamedCastExpr = CXXNamedCastExpr;

class CXXConstCastExpr extends CXXNamedCastExpr {
  get kind() {
    return "CXXConstCastExpr";
  }
}
exports.CXXConstCastExpr = CXXConstCastExpr;

class CXXDynamicCastExpr extends CXXNamedCastExpr {
  get kind() {
    return "CXXDynamicCastExpr";
  }
}
exports.CXXDynamicCastExpr = CXXDynamicCastExpr;

class CXXReinterpretCastExpr extends CXXNamedCastExpr {
  get kind() {
    return "CXXReinterpretCastExpr";
  }
}
exports.CXXReinterpretCastExpr = CXXReinterpretCastExpr;

class CXXStaticCastExpr extends CXXNamedCastExpr {
  get kind() {
    return "CXXStaticCastExpr";
  }
}
exports.CXXStaticCastExpr = CXXStaticCastExpr;
class ObjCBridgedCastExpr extends ExplicitCastExpr {
  get kind() {
    return "ObjCBridgedCastExpr";
  }
}
exports.ObjCBridgedCastExpr = ObjCBridgedCastExpr;
class ImplicitCastExpr extends CastExpr {
  get kind() {
    return "ImplicitCastExpr";
  }
}
exports.ImplicitCastExpr = ImplicitCastExpr;
class CharacterLiteral extends Expr {
  get kind() {
    return "CharacterLiteral";
  }
}
exports.CharacterLiteral = CharacterLiteral;

class ChooseExpr extends Expr {
  get kind() {
    return "ChooseExpr";
  }
}
exports.ChooseExpr = ChooseExpr;

class CompoundLiteralExpr extends Expr {
  get kind() {
    return "CompoundLiteralExpr";
  }
}
exports.CompoundLiteralExpr = CompoundLiteralExpr;

class ConvertVectorExpr extends Expr {
  get kind() {
    return "ConvertVectorExpr";
  }
}
exports.ConvertVectorExpr = ConvertVectorExpr;

class CoroutineSuspendExpr extends Expr {
  get kind() {
    return "CoroutineSuspendExpr";
  }
}
exports.CoroutineSuspendExpr = CoroutineSuspendExpr;

class CoawaitExpr extends CoroutineSuspendExpr {
  get kind() {
    return "CoawaitExpr";
  }
}
exports.CoawaitExpr = CoawaitExpr;

class CoyieldExpr extends CoroutineSuspendExpr {
  get kind() {
    return "CoyieldExpr";
  }
}
exports.CoyieldExpr = CoyieldExpr;
class DeclRefExpr extends Expr {
  get kind() {
    return "DeclRefExpr";
  }
}
exports.DeclRefExpr = DeclRefExpr;

class DependentCoawaitExpr extends Expr {
  get kind() {
    return "DependentCoawaitExpr";
  }
}
exports.DependentCoawaitExpr = DependentCoawaitExpr;

class DependentScopeDeclRefExpr extends Expr {
  get kind() {
    return "DependentScopeDeclRefExpr";
  }
}
exports.DependentScopeDeclRefExpr = DependentScopeDeclRefExpr;

class DesignatedInitExpr extends Expr {
  get kind() {
    return "DesignatedInitExpr";
  }
}
exports.DesignatedInitExpr = DesignatedInitExpr;

class DesignatedInitUpdateExpr extends Expr {
  get kind() {
    return "DesignatedInitUpdateExpr";
  }
}
exports.DesignatedInitUpdateExpr = DesignatedInitUpdateExpr;

class ExpressionTraitExpr extends Expr {
  get kind() {
    return "ExpressionTraitExpr";
  }
}
exports.ExpressionTraitExpr = ExpressionTraitExpr;

class ExtVectorElementExpr extends Expr {
  get kind() {
    return "ExtVectorElementExpr";
  }
}
exports.ExtVectorElementExpr = ExtVectorElementExpr;

class FixedPointLiteral extends Expr {
  get kind() {
    return "FixedPointLiteral";
  }
}
exports.FixedPointLiteral = FixedPointLiteral;

class FloatingLiteral extends Expr {
  get kind() {
    return "FloatingLiteral";
  }
}
exports.FloatingLiteral = FloatingLiteral;

class FullExpr extends Expr {
  get kind() {
    return "FullExpr";
  }
}
exports.FullExpr = FullExpr;

class ConstantExpr extends FullExpr {
  get kind() {
    return "ConstantExpr";
  }
}
exports.ConstantExpr = ConstantExpr;

class ExprWithCleanups extends FullExpr {
  get kind() {
    return "ExprWithCleanups";
  }
}
exports.ExprWithCleanups = ExprWithCleanups;
class FunctionParmPackExpr extends Expr {
  get kind() {
    return "FunctionParmPackExpr";
  }
}
exports.FunctionParmPackExpr = FunctionParmPackExpr;

class GNUNullExpr extends Expr {
  get kind() {
    return "GNUNullExpr";
  }
}
exports.GNUNullExpr = GNUNullExpr;

class GenericSelectionExpr extends Expr {
  get kind() {
    return "GenericSelectionExpr";
  }
}
exports.GenericSelectionExpr = GenericSelectionExpr;

class ImaginaryLiteral extends Expr {
  get kind() {
    return "ImaginaryLiteral";
  }
}
exports.ImaginaryLiteral = ImaginaryLiteral;

class ImplicitValueInitExpr extends Expr {
  get kind() {
    return "ImplicitValueInitExpr";
  }
}
exports.ImplicitValueInitExpr = ImplicitValueInitExpr;

class InitListExpr extends Expr {
  get kind() {
    return "InitListExpr";
  }
}
exports.InitListExpr = InitListExpr;

class IntegerLiteral extends Expr {
  get kind() {
    return "IntegerLiteral";
  }
}
exports.IntegerLiteral = IntegerLiteral;

class LambdaExpr extends Expr {
  get kind() {
    return "LambdaExpr";
  }
}
exports.LambdaExpr = LambdaExpr;

class MSPropertyRefExpr extends Expr {
  get kind() {
    return "MSPropertyRefExpr";
  }
}
exports.MSPropertyRefExpr = MSPropertyRefExpr;

class MSPropertySubscriptExpr extends Expr {
  get kind() {
    return "MSPropertySubscriptExpr";
  }
}
exports.MSPropertySubscriptExpr = MSPropertySubscriptExpr;

class MaterializeTemporaryExpr extends Expr {
  get kind() {
    return "MaterializeTemporaryExpr";
  }
}
exports.MaterializeTemporaryExpr = MaterializeTemporaryExpr;

class MemberExpr extends Expr {
  get kind() {
    return "MemberExpr";
  }
}
exports.MemberExpr = MemberExpr;

class NoInitExpr extends Expr {
  get kind() {
    return "NoInitExpr";
  }
}
exports.NoInitExpr = NoInitExpr;

class OMPArraySectionExpr extends Expr {
  get kind() {
    return "OMPArraySectionExpr";
  }
}
exports.OMPArraySectionExpr = OMPArraySectionExpr;

class ObjCArrayLiteral extends Expr {
  get kind() {
    return "ObjCArrayLiteral";
  }
}
exports.ObjCArrayLiteral = ObjCArrayLiteral;

class ObjCAvailabilityCheckExpr extends Expr {
  get kind() {
    return "ObjCAvailabilityCheckExpr";
  }
}
exports.ObjCAvailabilityCheckExpr = ObjCAvailabilityCheckExpr;

class ObjCBoolLiteralExpr extends Expr {
  get kind() {
    return "ObjCBoolLiteralExpr";
  }
}
exports.ObjCBoolLiteralExpr = ObjCBoolLiteralExpr;

class ObjCBoxedExpr extends Expr {
  get kind() {
    return "ObjCBoxedExpr";
  }
}
exports.ObjCBoxedExpr = ObjCBoxedExpr;

class ObjCDictionaryLiteral extends Expr {
  get kind() {
    return "ObjCDictionaryLiteral";
  }
}
exports.ObjCDictionaryLiteral = ObjCDictionaryLiteral;

class ObjCEncodeExpr extends Expr {
  get kind() {
    return "ObjCEncodeExpr";
  }
}
exports.ObjCEncodeExpr = ObjCEncodeExpr;

class ObjCIndirectCopyRestoreExpr extends Expr {
  get kind() {
    return "ObjCIndirectCopyRestoreExpr";
  }
}
exports.ObjCIndirectCopyRestoreExpr = ObjCIndirectCopyRestoreExpr;

class ObjCIsaExpr extends Expr {
  get kind() {
    return "ObjCIsaExpr";
  }
}
exports.ObjCIsaExpr = ObjCIsaExpr;

class ObjCIvarRefExpr extends Expr {
  get kind() {
    return "ObjCIvarRefExpr";
  }
}
exports.ObjCIvarRefExpr = ObjCIvarRefExpr;

class ObjCMessageExpr extends Expr {
  get kind() {
    return "ObjCMessageExpr";
  }
}
exports.ObjCMessageExpr = ObjCMessageExpr;

class ObjCPropertyRefExpr extends Expr {
  get kind() {
    return "ObjCPropertyRefExpr";
  }
}
exports.ObjCPropertyRefExpr = ObjCPropertyRefExpr;

class ObjCProtocolExpr extends Expr {
  get kind() {
    return "ObjCProtocolExpr";
  }
}
exports.ObjCProtocolExpr = ObjCProtocolExpr;

class ObjCSelectorExpr extends Expr {
  get kind() {
    return "ObjCSelectorExpr";
  }
}
exports.ObjCSelectorExpr = ObjCSelectorExpr;

class ObjCStringLiteral extends Expr {
  get kind() {
    return "ObjCStringLiteral";
  }
}
exports.ObjCStringLiteral = ObjCStringLiteral;

class ObjCSubscriptRefExpr extends Expr {
  get kind() {
    return "ObjCSubscriptRefExpr";
  }
}
exports.ObjCSubscriptRefExpr = ObjCSubscriptRefExpr;

class OffsetOfExpr extends Expr {
  get kind() {
    return "OffsetOfExpr";
  }
}
exports.OffsetOfExpr = OffsetOfExpr;

class OpaqueValueExpr extends Expr {
  get kind() {
    return "OpaqueValueExpr";
  }
}
exports.OpaqueValueExpr = OpaqueValueExpr;

class OverloadExpr extends Expr {
  get kind() {
    return "OverloadExpr";
  }
}
exports.OverloadExpr = OverloadExpr;

class UnresolvedLookupExpr extends OverloadExpr {
  get kind() {
    return "UnresolvedLookupExpr";
  }
}
exports.UnresolvedLookupExpr = UnresolvedLookupExpr;

class UnresolvedMemberExpr extends OverloadExpr {
  get kind() {
    return "UnresolvedMemberExpr";
  }
}
exports.UnresolvedMemberExpr = UnresolvedMemberExpr;
class PackExpansionExpr extends Expr {
  get kind() {
    return "PackExpansionExpr";
  }
}
exports.PackExpansionExpr = PackExpansionExpr;

class ParenExpr extends Expr {
  get kind() {
    return "ParenExpr";
  }
}
exports.ParenExpr = ParenExpr;

class ParenListExpr extends Expr {
  get kind() {
    return "ParenListExpr";
  }
}
exports.ParenListExpr = ParenListExpr;

class PredefinedExpr extends Expr {
  get kind() {
    return "PredefinedExpr";
  }
}
exports.PredefinedExpr = PredefinedExpr;

class PseudoObjectExpr extends Expr {
  get kind() {
    return "PseudoObjectExpr";
  }
}
exports.PseudoObjectExpr = PseudoObjectExpr;

class ShuffleVectorExpr extends Expr {
  get kind() {
    return "ShuffleVectorExpr";
  }
}
exports.ShuffleVectorExpr = ShuffleVectorExpr;

class SizeOfPackExpr extends Expr {
  get kind() {
    return "SizeOfPackExpr";
  }
}
exports.SizeOfPackExpr = SizeOfPackExpr;

class SourceLocExpr extends Expr {
  get kind() {
    return "SourceLocExpr";
  }
}
exports.SourceLocExpr = SourceLocExpr;

class StmtExpr extends Expr {
  get kind() {
    return "StmtExpr";
  }
}
exports.StmtExpr = StmtExpr;

class StringLiteral extends Expr {
  get kind() {
    return "StringLiteral";
  }
}
exports.StringLiteral = StringLiteral;

class SubstNonTypeTemplateParmExpr extends Expr {
  get kind() {
    return "SubstNonTypeTemplateParmExpr";
  }
}
exports.SubstNonTypeTemplateParmExpr = SubstNonTypeTemplateParmExpr;

class SubstNonTypeTemplateParmPackExpr extends Expr {
  get kind() {
    return "SubstNonTypeTemplateParmPackExpr";
  }
}
exports.SubstNonTypeTemplateParmPackExpr = SubstNonTypeTemplateParmPackExpr;

class TypeTraitExpr extends Expr {
  get kind() {
    return "TypeTraitExpr";
  }
}
exports.TypeTraitExpr = TypeTraitExpr;

class TypoExpr extends Expr {
  get kind() {
    return "TypoExpr";
  }
}
exports.TypoExpr = TypoExpr;

class UnaryExprOrTypeTraitExpr extends Expr {
  get kind() {
    return "UnaryExprOrTypeTraitExpr";
  }
}
exports.UnaryExprOrTypeTraitExpr = UnaryExprOrTypeTraitExpr;

class UnaryOperator extends Expr {
  get kind() {
    return "UnaryOperator";
  }
}
exports.UnaryOperator = UnaryOperator;

class VAArgExpr extends Expr {
  get kind() {
    return "VAArgExpr";
  }
}
exports.VAArgExpr = VAArgExpr;
class LabelStmt extends ValueStmt {
  get kind() {
    return "LabelStmt";
  }
}
exports.LabelStmt = LabelStmt;
class WhileStmt extends Stmt {
  get kind() {
    return "WhileStmt";
  }
}
exports.WhileStmt = WhileStmt;

class Type extends Node {
  get kind() {
    return "Type";
  }
}
exports.Type = Type;
class QualType extends Type {
  get kind() {
    return "QualType";
  }
}
exports.QualType = QualType;

class BuiltinType extends Type {
  get kind() {
    return "BuiltinType";
  }
}
exports.BuiltinType = BuiltinType;
class ComplexType extends Type {
  get kind() {
    return "ComplexType";
  }
}
exports.ComplexType = ComplexType;
class PointerType extends Type {
  get kind() {
    return "PointerType";
  }
}
exports.PointerType = PointerType;
class BlockPointerType extends Type {
  get kind() {
    return "BlockPointerType";
  }
}
exports.BlockPointerType = BlockPointerType;
class ReferenceType extends Type {
  get kind() {
    return "ReferenceType";
  }
}
exports.ReferenceType = ReferenceType;
class LValueReferenceType extends ReferenceType {
  get kind() {
    return "LValueReferenceType";
  }
}
exports.LValueReferenceType = LValueReferenceType;
class RValueReferenceType extends ReferenceType {
  get kind() {
    return "RValueReferenceType";
  }
}
exports.RValueReferenceType = RValueReferenceType;
class MemberPointerType extends Type {
  get kind() {
    return "MemberPointerType";
  }
}
exports.MemberPointerType = MemberPointerType;
class ArrayType extends Type {
  get kind() {
    return "ArrayType";
  }
}
exports.ArrayType = ArrayType;
class ConstantArrayType extends ArrayType {
  get kind() {
    return "ConstantArrayType";
  }
}
exports.ConstantArrayType = ConstantArrayType;
class IncompleteArrayType extends ArrayType {
  get kind() {
    return "IncompleteArrayType";
  }
}
exports.IncompleteArrayType = IncompleteArrayType;
class VariableArrayType extends ArrayType {
  get kind() {
    return "VariableArrayType";
  }
}
exports.VariableArrayType = VariableArrayType;
class DependentSizedArrayType extends ArrayType {
  get kind() {
    return "DependentSizedArrayType";
  }
}
exports.DependentSizedArrayType = DependentSizedArrayType;
class DependentSizedExtVectorType extends Type {
  get kind() {
    return "DependentSizedExtVectorType";
  }
}
exports.DependentSizedExtVectorType = DependentSizedExtVectorType;
class DependentAddressSpaceType extends Type {
  get kind() {
    return "DependentAddressSpaceType";
  }
}
exports.DependentAddressSpaceType = DependentAddressSpaceType;
class VectorType extends Type {
  get kind() {
    return "VectorType";
  }
}
exports.VectorType = VectorType;
class DependentVectorType extends Type {
  get kind() {
    return "DependentVectorType";
  }
}
exports.DependentVectorType = DependentVectorType;
class ExtVectorType extends VectorType {
  get kind() {
    return "ExtVectorType";
  }
}
exports.ExtVectorType = ExtVectorType;
class FunctionType extends Type {
  get kind() {
    return "FunctionType";
  }
}
exports.FunctionType = FunctionType;
class FunctionProtoType extends FunctionType {
  get kind() {
    return "FunctionProtoType";
  }
}
exports.FunctionProtoType = FunctionProtoType;
class FunctionNoProtoType extends FunctionType {
  get kind() {
    return "FunctionNoProtoType";
  }
}
exports.FunctionNoProtoType = FunctionNoProtoType;
class UnresolvedUsingType extends Type {
  get kind() {
    return "UnresolvedUsingType";
  }
}
exports.UnresolvedUsingType = UnresolvedUsingType;
class ParenType extends Type {
  get kind() {
    return "ParenType";
  }
}
exports.ParenType = ParenType;
class TypedefType extends Type {
  get kind() {
    return "TypedefType";
  }
}
exports.TypedefType = TypedefType;
class MacroQualifiedType extends Type {
  get kind() {
    return "MacroQualifiedType";
  }
}
exports.MacroQualifiedType = MacroQualifiedType;
class AdjustedType extends Type {
  get kind() {
    return "AdjustedType";
  }
}
exports.AdjustedType = AdjustedType;
class DecayedType extends AdjustedType {
  get kind() {
    return "DecayedType";
  }
}
exports.DecayedType = DecayedType;
class TypeOfExprType extends Type {
  get kind() {
    return "TypeOfExprType";
  }
}
exports.TypeOfExprType = TypeOfExprType;
class TypeOfType extends Type {
  get kind() {
    return "TypeOfType";
  }
}
exports.TypeOfType = TypeOfType;
class DecltypeType extends Type {
  get kind() {
    return "DecltypeType";
  }
}
exports.DecltypeType = DecltypeType;
class UnaryTransformType extends Type {
  get kind() {
    return "UnaryTransformType";
  }
}
exports.UnaryTransformType = UnaryTransformType;
class TagType extends Type {
  get kind() {
    return "TagType";
  }
}
exports.TagType = TagType;
class RecordType extends TagType {
  get kind() {
    return "RecordType";
  }
}
exports.RecordType = RecordType;
class EnumType extends TagType {
  get kind() {
    return "EnumType";
  }
}
exports.EnumType = EnumType;
class ElaboratedType extends Type {
  get kind() {
    return "ElaboratedType";
  }
}
exports.ElaboratedType = ElaboratedType;
class AttributedType extends Type {
  get kind() {
    return "AttributedType";
  }
}
exports.AttributedType = AttributedType;
class TemplateTypeParmType extends Type {
  get kind() {
    return "TemplateTypeParmType";
  }
}
exports.TemplateTypeParmType = TemplateTypeParmType;
class SubstTemplateTypeParmType extends Type {
  get kind() {
    return "SubstTemplateTypeParmType";
  }
}
exports.SubstTemplateTypeParmType = SubstTemplateTypeParmType;
class SubstTemplateTypeParmPackType extends Type {
  get kind() {
    return "SubstTemplateTypeParmPackType";
  }
}
exports.SubstTemplateTypeParmPackType = SubstTemplateTypeParmPackType;
class TemplateSpecializationType extends Type {
  get kind() {
    return "TemplateSpecializationType";
  }
}
exports.TemplateSpecializationType = TemplateSpecializationType;
class DeducedType extends Type {
  get kind() {
    return "DeducedType";
  }
}
exports.DeducedType = DeducedType;
class AutoType extends DeducedType {
  get kind() {
    return "AutoType";
  }
}
exports.AutoType = AutoType;
class DeducedTemplateSpecializationType extends DeducedType {
  get kind() {
    return "DeducedTemplateSpecializationType";
  }
}
exports.DeducedTemplateSpecializationType = DeducedTemplateSpecializationType;
class InjectedClassNameType extends Type {
  get kind() {
    return "InjectedClassNameType";
  }
}
exports.InjectedClassNameType = InjectedClassNameType;
class DependentNameType extends Type {
  get kind() {
    return "DependentNameType";
  }
}
exports.DependentNameType = DependentNameType;
class DependentTemplateSpecializationType extends Type {
  get kind() {
    return "DependentTemplateSpecializationType";
  }
}
exports.DependentTemplateSpecializationType = DependentTemplateSpecializationType;
class PackExpansionType extends Type {
  get kind() {
    return "PackExpansionType";
  }
}
exports.PackExpansionType = PackExpansionType;
class ObjCTypeParamType extends Type {
  get kind() {
    return "ObjCTypeParamType";
  }
}
exports.ObjCTypeParamType = ObjCTypeParamType;
class ObjCObjectType extends Type {
  get kind() {
    return "ObjCObjectType";
  }
}
exports.ObjCObjectType = ObjCObjectType;
class ObjCInterfaceType extends ObjCObjectType {
  get kind() {
    return "ObjCInterfaceType";
  }
}
exports.ObjCInterfaceType = ObjCInterfaceType;
class ObjCObjectPointerType extends Type {
  get kind() {
    return "ObjCObjectPointerType";
  }
}
exports.ObjCObjectPointerType = ObjCObjectPointerType;
class PipeType extends Type {
  get kind() {
    return "PipeType";
  }
}
exports.PipeType = PipeType;
class AtomicType extends Type {
  get kind() {
    return "AtomicType";
  }
}
exports.AtomicType = AtomicType;
