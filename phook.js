let tickPromise = Promise.resolve();
tickPromise.constructor = Promise;
let schedule = tickPromise.then.bind(tickPromise);
let tick = 0;
another = () =>
  schedule(() => {
    console.log("tick", ++tick);
    if (tick < 10) another();
  });
another();

let constructCalls = 0;

Promise = (BasePromise => {
  let promiseIdCounter = 0;

  function getThenableThen(v) {
    if (v == null) return;
    const then = v.then;
    if (typeof then !== "function") return;
    return then;
  }

  const sMainFunction = Symbol();
  let context = sMainFunction; // Main() function.

  function format(promise) {
    if (promise instanceof Promise) {
      if (promise.hooked) {
        return `<P.${promise.id || "??"}>`;
      } else {
        return `<B.${promise.id || "??"}>`;
      }
    } else if (getThenableThen(promise)) {
      return `<Thenable:${promise}>`;
    } else if (promise === sMainFunction) {
      return "<Main>";
    } else if (promise == null) {
      return "<None>";
    } else {
      return "<Error>";
    }
  }

  function log(header, type, promise, parent, ...extra) {
    let ctx = String(format(context)).padEnd(6);
    let parInfo = parent ? [format(parent), "~"] : [];
    console.log(ctx, header, type, ...parInfo, format(promise), ...extra);
  }

  function beginHook(...args) {
    log("{ ==>", ...args);
  }

  function endHook(...args) {
    log("}  //", ...args);
  }

  function spotHook(...args) {
    log("     ", ...args);
  }

  function beginContext(...args) {
    context = args[1]; // Promise, thenable etc.
    beginHook(...args);
  }

  function endContext(...args) {
    endHook(...args);
    context = null;
  }

  var makeThenableHook = (thenable, then, parent) => {
    return {
      then: (resolve, reject) => {
        try {
          beginContext("CallThenable", thenable, parent);
          resolve = makeResolveHook(resolve, thenable, parent);
          reject = makeRejectHook(reject, thenable, parent);
          return then.call(thenable, resolve, reject);
        } finally {
          endContext("CallThenable", thenable, parent);
        }
      }
    };
  };

  var makeResolveHook = (resolve, promise, parent) => {
    return result => {
      const then = getThenableThen(result);
      resolve(then ? makeThenableHook(result, then) : result);
      spotHook("Resolve", promise, parent, result);
    };
  };

  var makeRejectHook = (reject, promise, parent) => reason => {
    reject(result);
    spotHook("Reject", promise, parent, reason);
  };

  function makeFulfilmentHook(fn, type, promise, parent) {
    if (typeof fn !== "function") return fn;
    return (...args) => {
      beginContext(`PromiseReaction:${type}`, promise, parent, ...args);
      let rv;
      try {
        return (rv = fn(...args));
      } finally {
        endContext(`PromiseReaction:${type}`, promise, parent, rv);
      }
    };
  }

  function init(promise, delegate = null) {
    constructCalls++;
    promise.id = ++promiseIdCounter;
    promise.delegate = delegate;
    promise.hooked = true;
  }

  function create(delegate = null) {
    const promise = Object.create(Promise.prototype);
    init(promise, delegate);
    return promise;
  }

  function Promise(start) {
    const promise = this;
    init(promise);
    beginHook("new Promise", promise);
    promise.delegate = new BasePromise((resolve, reject) => {
      resolve = makeResolveHook(resolve, promise);
      reject = makeRejectHook(reject, promise);
      return start(resolve, reject);
    });
    endHook("new Promise", promise);
  }

  Object.setPrototypeOf(Promise.prototype, BasePromise.prototype);
  //Object.defineProperties(Promise, Object.getOwnPropertyDescriptors(BasePromise))
  Object.defineProperties(
    Promise.prototype,
    Object.getOwnPropertyDescriptors(BasePromise.prototype)
  );

  Promise.prototype.then = function(onresolved, onrejected) {
    const promise = create();
    onresolved = makeFulfilmentHook(onresolved, "Resolved", promise, this);
    onrejected = makeFulfilmentHook(onrejected, "Rejected", promise, this);
    promise.delegate = this.delegate.then(onresolved, onrejected);
    spotHook("Promise.then", promise, this)
    return promise;
  };

  Promise.resolve = function(...args) {
    return create(BasePromise.resolve(...args));
  };

  return Promise;
})(Promise);

const last = new Promise((res, rej) => {
  res(Promise.resolve(41).then(v => (console.log("yay1"), v)));
})
  .then(res => {
    return new Promise(res => setTimeout(res, 1000)).then(() => "ok");
  })
  .then(res => {
    console.log("did it:", res);
  });

async function af() {
  console.log("sync");
  let r = await Promise.resolve(22).then(v => {
    console.log("hello!");
    //throw "NOOO"
    return v * 2;
  });
  console.log("^ await promise", r);
  let v = await 1234;
  console.log("^ await primitive", v);
  let t = await {
    then(s) {
      s(12);
    }
  };
  console.log("^ await thenable", t);
}
//x = af();
