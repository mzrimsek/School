//
//  SecondViewController.swift
//  KaleidoTab
//
//  Created by Mike Zrimsek on 3/22/17.
//  Copyright © 2017 Mike Zrimsek. All rights reserved.
//

import UIKit

class ConfigViewController: UIViewController {
    
    var kaleidoViewViewContoller : KaleidoViewViewController?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        kaleidoViewViewContoller = tabBarController?.viewControllers?[0] as? KaleidoViewViewController
    }
}

