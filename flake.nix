{
  description = "A small 2D ECS engine I built to better understand low-level game programming and engine design.";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }: 
    let
      pkgs = nixpkgs.legacyPackages.x86_64-linux;
      
      buildDeps = with pkgs; [
        # packages needed on runtime of the program
        sdl2
        lua
      ];
      
      nativeDeps = with pkgs;[
        # packages needed to build the project
      ];
      
      sharedEnv = {
        # environment for nix shell and build time
      };
      
    in {
      packages.x86_64-linux.default = pkgs.stdenv.mkDerivation ({
        pname = "2d-ecs-engine"; # change
        version = "1.0.0";
        src = ./.;
        buildInputs = buildDeps;
        nativeBuildInputs = nativeDeps;
        #buildPhase = '' '';
        #installPhase = '' '';
      } // sharedEnv);

      devShells.x86_64-linux.default = pkgs.mkShell ({
        buildInputs = buildDeps ++ nativeDeps;
      } // sharedEnv);
    };
}
