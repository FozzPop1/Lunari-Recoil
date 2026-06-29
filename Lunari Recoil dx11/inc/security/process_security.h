#pragma once
#include <windows.h>

namespace ProcessSecurity {

    inline void EnableMitigations() {
        PROCESS_MITIGATION_EXTENSION_POINT_DISABLE_POLICY ext = {};
        ext.DisableExtensionPoints = 1;
        SetProcessMitigationPolicy(ProcessExtensionPointDisablePolicy, &ext, sizeof(ext));

        PROCESS_MITIGATION_CHILD_PROCESS_POLICY child = {};
        child.NoChildProcessCreation = 1;
        SetProcessMitigationPolicy(ProcessChildProcessPolicy, &child, sizeof(child));

        PROCESS_MITIGATION_DEP_POLICY dep = {};
        dep.Enable = 1;
        dep.Permanent = 1; // Cannot be disabled at runtime
        SetProcessMitigationPolicy(ProcessDEPPolicy, &dep, sizeof(dep));

        PROCESS_MITIGATION_ASLR_POLICY aslr = {};
        aslr.EnableBottomUpRandomization = 1;
        aslr.EnableForceRelocateImages = 1;
        aslr.EnableHighEntropy = 1;       // 64-bit: much larger address space
        aslr.DisallowStrippedImages = 1;  // Reject DLLs without relocation info
        SetProcessMitigationPolicy(ProcessASLRPolicy, &aslr, sizeof(aslr));

        PROCESS_MITIGATION_BINARY_SIGNATURE_POLICY sig = {};
        sig.MicrosoftSignedOnly = 1;
        // sig.StoreSignedOnly = 1;     // Optional: only allow Store-signed
        // sig.MitigationOptIn = 1;     // Optional: opt into strict mode
        SetProcessMitigationPolicy(ProcessSignaturePolicy, &sig, sizeof(sig));

        PROCESS_MITIGATION_CONTROL_FLOW_GUARD_POLICY cfg = {};
        cfg.EnableControlFlowGuard = 1;
        cfg.EnableExportSuppression = 1;  // Hide export table from CFG checks
        cfg.StrictMode = 1;               // Stricter enforcement
        SetProcessMitigationPolicy(ProcessControlFlowGuardPolicy, &cfg, sizeof(cfg));

        PROCESS_MITIGATION_IMAGE_LOAD_POLICY img = {};
        img.NoRemoteImages = 1;           // No DLLs from network paths
        img.NoLowMandatoryLabelImages = 1;// No low-integrity DLLs
        img.PreferSystem32Images = 1;     // Prefer System32 over app dir
        SetProcessMitigationPolicy(ProcessImageLoadPolicy, &img, sizeof(img));
    }

}