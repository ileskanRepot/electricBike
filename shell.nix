{ pkgs ? import <nixpkgs> {}}:
  pkgs.mkShell {
    nativeBuildInputs = let
      env = pyPkgs : with pyPkgs; [
      ];
    in with pkgs; [
      (python311.withPackages env)
      arduino
  ];
}
