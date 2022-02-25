package com.discord
{
   import flash.events.EventDispatcher;
   import flash.events.IEventDispatcher;
   import flash.events.StatusEvent;
   import flash.external.ExtensionContext;
   
   public class DiscordExtension extends EventDispatcher
   {
      
      private static const EXTENSION_ID:String = "com.discord.DiscordExtension";
       
      
      private var m_extContext:ExtensionContext = null;
      
      public function DiscordExtension(target:IEventDispatcher = null)
      {
         super(target);
         m_extContext = ExtensionContext.createExtensionContext(EXTENSION_ID,null);
         m_extContext.addEventListener("status",onStatusEvent);
      }
      
      private function onStatusEvent(_event:StatusEvent) : void
      {
         trace("Event code: " + _event.code + ", event level: " + _event.level);
      }
      
      public function sendPresence(_state:String, _details:String, _largeImageKey:String, _smallImageKey:String) : String
      {
         return m_extContext.call("as_sendPresence",_state,_details,_largeImageKey,_smallImageKey) as String;
      }
   }
}
