etSureClickListener(dialog -> {
    String F= binding.etNumberOfBuildingFloors.getText().toString();
    String A= binding.etBuildingBaseArea.getText().toString();
    String H= binding.etBuildingFloorHeight.getText().toString();
    String P= binding.etPerimeter.getText().toString();
    String AF = ArithmeticUtils.mul(A, F).toString();
    String AF2= ArithmeticUtils.mul( AF  ,"2").toString();
    String FH=ArithmeticUtils.mul(F, H).toString();
    String FHP=ArithmeticUtils.mul(FH,P).toString();
    String FHP2=ArithmeticUtils.mul(FHP,"2").toString();
    BigDecimal add = ArithmeticUtils.add(ArithmeticUtils.add(AF2, FHP2).toString(),A);
    double Ae = add.doubleValue();
    double m=0;
    double n=0;

    if (binding.buildingType.getSelectedItemPosition()==0){
        m=0.368;
        n=0.992;
    }
    if (binding.buildingType.getSelectedItemPosition()==1){
        m=0.511;
        n=0.976;
    }
    if (binding.buildingType.getSelectedItemPosition()==2){
        m=0.523;
        n=0.968;
    }
    if (binding.buildingType.getSelectedItemPosition()==3){
        m=0.421;
        n=0.985;
    }
    if (binding.buildingType.getSelectedItemPosition()==4){
        m=0.479;
        n=0.980;
    }
    double Aen = Math.pow(Ae, n);
    double t0_5 = Math.pow(Double.parseDouble(binding.etCompletionPeriod.getText().toString()), 0.5);
    double a = mapArrayList.get(binding.cementType.getSelectedItemPosition()).get((String) binding.cementStrength.getSelectedItem());

    String Nabc=ArithmeticUtils.mul(
        ArithmeticUtils.mul(
            ArithmeticUtils.mul(
                binding.etNumberOfBuildings.getText().toString(),String.valueOf(a)
                               )
                .toString(),""+concreteStrengthGrade.get((String) binding.concreteStrengthGrade.getSelectedItem())
                            )
                .toString(),""+buildingStructureType.get(binding.buildingStructureType.getSelectedItemPosition())
                                  ).toString();

    double y=ArithmeticUtils.mul(String.valueOf(ArithmeticUtils.mul(ArithmeticUtils.mul(m,Aen),t0_5)),Nabc).doubleValue();
    binding.tvResult.setText(""+Math.round(y));
}