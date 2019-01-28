import { Component } from '@angular/core';
import { IonicPage, NavController, NavParams } from 'ionic-angular';
import {  Config } from '../../../../providers/Config';
/**
 * Generated class for the NodeinformationPage page.
 *
 * See https://ionicframework.com/docs/components/#navigation for more info on
 * Ionic pages and navigation.
 */

@IonicPage()
@Component({
  selector: 'page-nodeinformation',
  templateUrl: 'nodeinformation.html',
})
export class NodeinformationPage {
  public countrys=[];
  public  isStatus:boolean = false;
  public info= {};
  public masterId:string ="1";
  constructor(public navCtrl: NavController, public navParams: NavParams) {
         this.info = this.navParams.data["info"];
         this.masterId = Config.getCurMasterWalletId();
         this.countrys = Config.getAllCountry();
         console.log("==========NodeinformationPage"+this.info);
        //  if(this.navParams.data["status"] === 0){
        //           this.isStatus = false;
        //  }else if(this.navParams.data["status"] === 1){
        //           this.isStatus = true;
        //  }
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad NodeinformationPage');
  }

  lookOver(){
   this.navCtrl.pop();
  }

  delList(parms){

  }

  addList(parms){

  }

  public getCountryByCode(code){

    for(let index in this.countrys){
        let item = this.countrys[index];
        if(code === item["code"]){
          return item["key"];
        }
       return "Unknown";
      }
  }

}
