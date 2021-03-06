// Copyright (c) 2019, the Dart project authors.  Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE file.

// SharedOptions=--enable-experiment=non-nullable

// Invalid uses of "required" modifier

required //# 01: compile-time error
int f1(
  required //# 02: compile-time error
  int x
) {}

required //# 03: compile-time error
class C1 {
  required //# 04: compile-time error
  int f2;
}

// Duplicate modifier
void f2({
  required
  required //# 05: compile-time error
  int i,
}){
}

// Out of order modifiers
class C2 {
  void m({
    covariant
    required //# 07: compile-time error
    int i2,
    final
    required //# 08: compile-time error
    int i3,
  }) {
  }
}

main() {
}
