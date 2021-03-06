// Copyright (c) 2016, the Dart project authors.  Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE file.

#ifndef RUNTIME_VM_KERNEL_ISOLATE_H_
#define RUNTIME_VM_KERNEL_ISOLATE_H_

#include <vector>

#include "include/dart_api.h"
#include "include/dart_native_api.h"

#include "vm/allocation.h"
#include "vm/dart.h"
#include "vm/os_thread.h"

namespace dart {

// TODO(33433): The kernel service does not belong in the VM.

class KernelIsolate : public AllStatic {
 public:
  static const char* kName;
  static const int kCompileTag;
  static const int kUpdateSourcesTag;
  static const int kAcceptTag;
  static const int kTrainTag;
  static const int kCompileExpressionTag;
  static const int kListDependenciesTag;
  static const int kNotifyIsolateShutdown;

  static void Run();
  static void Shutdown();

  static bool NameEquals(const char* name);
  static bool Exists();
  static bool IsRunning();
  static bool IsKernelIsolate(const Isolate* isolate);
  static Dart_Port WaitForKernelPort();
  static Dart_Port KernelPort() { return kernel_port_; }

  static Dart_KernelCompilationResult CompileToKernel(
      const char* script_uri,
      const uint8_t* platform_kernel,
      intptr_t platform_kernel_size,
      int source_files_count = 0,
      Dart_SourceFile source_files[] = NULL,
      bool incremental_compile = true,
      const char* package_config = NULL,
      const char* multiroot_filepaths = NULL,
      const char* multiroot_scheme = NULL);

  static Dart_KernelCompilationResult AcceptCompilation();
  static Dart_KernelCompilationResult UpdateInMemorySources(
      int source_files_count,
      Dart_SourceFile source_files[]);

  static Dart_KernelCompilationResult CompileExpressionToKernel(
      const char* expression,
      const Array& definitions,
      const Array& type_definitions,
      const char* library_url,
      const char* klass,
      bool is_static);

  static Dart_KernelCompilationResult ListDependencies();

  static void NotifyAboutIsolateShutdown(const Isolate* isolate);

  static void AddExperimentalFlag(const char* value);

 protected:
  static void InitCallback(Isolate* I);
  static void SetKernelIsolate(Isolate* isolate);
  static void SetLoadPort(Dart_Port port);
  static void FinishedExiting();
  static void FinishedInitializing();
  static void InitializingFailed();
  static Dart_IsolateCreateCallback create_callback() {
    return create_callback_;
  }

  static Dart_IsolateCreateCallback create_callback_;
  static Monitor* monitor_;
  enum State {
    kStopped,
    kStarting,
    kStarted,
    kStopping,
  };
  static State state_;
  static Isolate* isolate_;
  static Dart_Port kernel_port_;

  static MallocGrowableArray<char*>* experimental_flags_;

  friend class Dart;
  friend class Isolate;
  friend class RunKernelTask;
};

}  // namespace dart

#endif  // RUNTIME_VM_KERNEL_ISOLATE_H_
