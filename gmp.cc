#include <math.h>
#include <string.h>
#include <v8.h>
#include <node.h>

#include <stdio.h>
#include <stdarg.h>
#include <obstack.h>
#include <gmp.h>
#include <gmpxx.h>

using namespace v8;
using namespace node;

// http://github.com/embedthis/packages/blob/a0123bc7a4728dd1b4eec012d46f2bf45ae3c8f0/php/php-5.3.2/ext/gmp/gmp.c

Handle<Value>
noop(const Arguments &args) {
  return Undefined();
}

Handle<Value>
add(const Arguments &args) {
  HandleScope scope;
  if (args[0]->IsNumber() && args[1]->IsNumber()) {
    Local<Integer> res = Integer::New(args[0]->Int32Value() + args[1]->Int32Value());
    return scope.Close(res);
  } else {
    return ThrowException(Exception::Error(String::New("invalid argument error!")));
  }
}

extern "C" void
init (Handle<Object> target)
{
  HandleScope scope;

  target->Set(String::New("version"), String::New(gmp_version));
  target->Set(String::New("str"), String::New("i am a string!"));
  target->Set(String::New("num"), Number::New(34));
  NODE_SET_METHOD(target, "add", add);
}
