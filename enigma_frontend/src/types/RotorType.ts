enum RotorName {
  I = 0,
  II,
  III,
  IV,
  V,
  VI,
  VII,
  VIII,
}

type RotorType = {
  name: RotorName;
  rotorPosition: number;
  ringSetting: number;
};
