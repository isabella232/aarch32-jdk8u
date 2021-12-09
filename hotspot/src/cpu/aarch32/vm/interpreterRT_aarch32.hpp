/*
 * Copyright (c) 1998, 2010, Oracle and/or its affiliates. All rights reserved.
 * Copyright (c) 2014, Red Hat Inc. All rights reserved.
 * Copyright (c) 2015, Linaro Ltd. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#ifndef CPU_AARCH32_VM_INTERPRETERRT_AARCH32_HPP
#define CPU_AARCH32_VM_INTERPRETERRT_AARCH32_HPP

#include "asm/macroAssembler.hpp"
#include "memory/allocation.hpp"

// native method calls

class SignatureHandlerGenerator: public NativeSignatureIterator {
 private:
  MacroAssembler* _masm;
  unsigned int _fp_arg_mask;
  int _num_int_args;
  unsigned _next_double_dex;
  int _stack_offset;

  void pass_int();
  void pass_long();
  void pass_float();
  void pass_double();
  void pass_object();

 public:
  // Creation
  SignatureHandlerGenerator(methodHandle method, CodeBuffer* buffer):
   NativeSignatureIterator(method),
   _next_double_dex(0),
   _stack_offset(0)
  {
    _masm = new MacroAssembler(buffer);
    _num_int_args = (method->is_static() ? 1 : 0);
    // See layout in interpreter_aarch32.cpp
    _fp_arg_mask =  (1 <<(Argument::n_float_register_parameters_c * 3)) - 1;
  }

  // Code generation
  void generate(uint64_t fingerprint);

  // Code generation support
  static Register from();
  static Register to();
  static Register temp();
};

#endif // CPU_AARCH32_VM_INTERPRETERRT_AARCH32_HPP
