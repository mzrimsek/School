//
//  ViewController.swift
//  exercise-2
//
//  Created by Mike Zrimsek on 2/21/17.
//  Copyright © 2017 Mike Zrimsek. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var label: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    @IBAction func onButtonClick(_ sender: Any) {
        label.text = label.text! + "!";
    }
    
}

