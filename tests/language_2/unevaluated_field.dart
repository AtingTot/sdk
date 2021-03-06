// Copyright (c) 2019, the Dart project authors.  Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE file.

// SharedOptions=--enable-experiment=constant-update-2018

// Test that environment constants in field initializers work properly.

import "package:expect/expect.dart";

const int gx = const int.fromEnvironment("x");

class A {
  final int x = gx;
  final int y = const int.fromEnvironment("y");
  const A();
}

main() {
  const a = const A();
  Expect.isTrue(a.x == null || a.x != null);
  Expect.isTrue(a.y == null || a.y != null);
}
