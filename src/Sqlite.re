module Statement = {
  type t;

  [@bs.send] [@bs.splice]
  external all: (t, array('a)) => Js.Array.t(Js.Json.t) ="all";

  [@bs.send] external all_named: (t, 'a) => Js.Json.t = "all";

  [@bs.send] [@bs.splice] external get: (t, array('a)) => Js.Json.t ="get";

  [@bs.send] external get_named: (t, 'a) => Js.Json.t = "get";

  [@bs.send] [@bs.splice] external run: (t, array('a)) => Js.Json.t ="run";

  [@bs.send] external run_named: (t, 'a) => Js.Json.t = "run";

  [@bs.get] external returns_data: t => bool = "returnsData";

  [@bs.get] external source: t => string = "source";
};

module Connection = {
  type t;

  module Config = {
    type t;

    [@bs.obj]
    external make:
      (
        ~memory: bool=?,
        ~readonly: bool=?,
        ~fileMustExist: bool=?,
        unit
      ) =>
      t;
  };

  [@bs.module] [@bs.new]
  external connect: (string, Config.t) => t = "better-sqlite3";

  [@bs.send] external close: t => unit ="close";

  let make = (~path, ~memory=?, ~readonly=?, ~fileMustExist=?, _) =>
    connect(path, Config.make(~memory?, ~readonly?, ~fileMustExist?, ()));

  [@bs.send] external prepare: (t, string) => Statement.t = "prepare";

  [@bs.get] external is_open: t => bool = "open";

  [@bs.get] external in_transaction: t => bool = "inTransaction";

  [@bs.get] external name: t => string = "name";

  [@bs.get] external memory: t => bool="memory";

  [@bs.get] external readonly: t => bool="readonly";
};

