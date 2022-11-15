function z_out=saleh(z_in)

  r_d=abs(z_in);
  A=2./(1+r_d.^2);
  Ph=(pi/3).*(r_d.^2)./(1+r_d.^2);
  z_out=z_in.*A.*exp(j.*Ph);
  
